const weather = require('weather-js')
const reactions = require('./reactions')
const googleTrends = require('google-trends-api');

module.exports = function(User) {

	const Reactions = reactions()

	var Services = function(service) {
		this.name = service.name
		this.id = service.id
	}


	Services.createTrends = function createTrends(body, callback) {
		User.updateService(body.username, 'subject', body.subject, callback)
	}

  Services.refreshTrends = function refreshTrends(subject, username, email, User, callback) {
		googleTrends.interestOverTime({keyword: subject})
		.then(function(results){
			Reactions.react(username, 'email', {email: email, subject:'Trends news !', content:'A news is available about ' + subject}, User, {service: 'trends', value: 'NULL'},function(res) {
			})

		})
      .catch(function(err){
			callback(400)
		});
	}


	Services.createWeather = function createWeather(body, callback) {
		weather.find({search: body.city, degreeType: 'C'}, function(err, result) {
			if (!err) {
				User.updateService(body.username, 'city', body.city, callback)
			} else {
				console.log('Something happened while creating the weather service')
				callback(400)
			}
		});
	}

	Services.createTimer = function createTimer(body, callback) {
		// Il va falloir save la date dans la sql
		User.updateService(body.username, 'date', body.date, callback)
	}

  Services.refreshWeather = function refreshWeather(city, callback) {
		if (city != 'NULL') {
			weather.find({search: city, degreeType: 'C'}, function(err, result) {
				if (result[0].current.skytext == 'Light Rain')
				callback(200)
				else
				callback(300)
				// Il faut comparer ici pour savoir si on a ce que l'on souhaite
			});
		} else {
			callback(300)
		}
	}

	//Services.

	Services.refreshTimer = function refreshTimer(date, callback) {
		var curDate = new Date()
		if (date != '0000-00-00 00:00:00' && date.getTime() < curDate.getTime()) {
			callback(200)
		} else {
			callback(300)
		}
	}

	Services.refreshAll = function refreshAll(username, email, User, callback) {
		console.log('Refreshing')
		User.getServices(username, function(services) {
			if (services['date']) {
				Services.refreshTimer(services['date'], function(code) {
					if (code == 200) {
						Reactions.react(username, 'notif', {email: email, subject:'alarm', content:'Timer is over'}, User, {service: 'date', value: '0000:00:00 00:00:00'}, function(res) {
							callback(res)
						})
					}
				})
			}
			if (services['city']) {
				Services.refreshWeather(services['city'], function(code) {
					if (code == 200) {
						Reactions.react(username, 'email', {email: email, subject:'alarm', content:'Its raining in ' + services['city']}, User, {service: 'city', value: 'NULL'},function(res) {
							callback(res)
						})
					}
				})
			}
			if (services['subject']) {
                          Services.refreshTrends(services['subject'], username, email, User, function(code) {
                            callback(code)
                          })
			}
			callback(200)
		})
	}

  Services.add = function addService(body, callback) {
		if (body.service == 'timer')
			this.createTimer(body, callback)
		else if (body.service == 'weather') {
			this.createWeather(body, callback)
		} else if (body.service == 'trends') {
			this.createTrends(body, callback)
		} else {
			callback('400 Service unknown')
		}
	}

	return Services
}
