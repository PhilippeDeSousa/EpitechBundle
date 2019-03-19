const GoogleAuthentifier = require('./googleAuthentifier')
const OfficeAuthentifier = require('./officeAuthentifier')
const About = require('./about')
const model = require('./userModel')
const services = require('./services')
const weather = require('weather-js')

module.exports = function(app, area) {

	const User = model(area)
    const Services = services(User)
    const googleAuthentifier = GoogleAuthentifier(app)
    const officeAuthentifier = OfficeAuthentifier(app, User)

	let notifs = ''
	let alert = ''

    app.get('/', (req, res) => {
        res.send('If the user isnt logged in, there should be a Login page, else it should redirect him to the service page')
    })

    app.use('/signup', (req, res) => {
        var redirectValue = ""
        if (req.query.return)
            redirectValue = req.query.return
        var user = new User(req.body)
        User.create(user, function (ret) {
            if (redirectValue != "")
                res.redirect(redirectValue)
            else
                res.send(ret)
        })
    })

	app.use('/login', (req, res) => {
	    var redirectValue = ""
        if (req.query.return)
            redirectValue = req.query.return
		var user = {username: req.body.username, password: req.body.password}
		User.login(user, function(err, ret) {
			if (err) {
				res.sendStatus(403)
			}
			else {
				User.createToken(user, function(err, token) {
					if (err)
						res.sendStatus(403)
					else {
						res.send({token: token});
					}
				})
			}
		})
	})

    /* Technically, this road should never exist */
    app.post('/delete', (req, res) => {
        var username = req.body.username
        var password = req.body.password
        User.delete(username, password, function (ret) {
            res.sendStatus(ret)
        })
    })

    app.get('/about.json', (req, res) => {
        res.send(About.CreateJson(req, res))
    })

    app.get('/auth/office', (req, res) => {
        officeAuthentifier.authOffice(req, res, function(params) {
			console.log('Sending in the params')
            res.send(params)
        })
    })

	app.use((req, res, next) => {
        if (req.query.token) {
			User.getUsername(req.query.token, function(err, ret) {
				if (err)
					res.send(err)
				else {
					req.body.username = ret
					next()
				}
			})
        } else {
            res.status(401).send('You must be logged in to see this page')
        }
    })

	app.get('/notifs', (req, res) => {
		if (notifs != '') {
			res.send(200, notifs)
		} else if (alert != '') {
			res.send(201, alert)
		} else {
			res.sendStatus(300)
		}
	})

	app.post('/add', (req, res) => {
		Services.add(req.body, function(ret) {
			User.getEmail(req.query.token, function(err, email) {
				if (email) {
					setInterval(function() { Services.refreshAll(req.body.username, email, User, function(retu) {
						if (retu.content)
							notifs = retu.content
					}) }, 10*1000);
				}
				res.sendStatus(200)
			})
		 })
	})

	app.post('/subscribe', (req, res) => {
        if (!req.body.service) {
            res.sendStatus(400)
        } else {
    		User.subscribe(req.body.username, req.body.service, function(ret) {
				res.sendStatus(ret)
    		})
        }
	})

	app.post('/unsubscribe', (req, res) => {
		if (!req.body.service) {
			res.sendStatus(400)
		} else {
			User.unsubscribe(req.body.username, req.body.service, function(ret) {
				res.sendStatus(ret)
			})
		}
	})

	app.get('/dashboard', (req, res) => {
		//Il faut refresh toutes les AREA des utilisateurs
		res.send("Doing").status(200)
	})

    app.use('/auth/google', (req, res) => {
        googleAuthentifier.authGoogle(req, res, function(url) {
            res.send({ authUrl :url })
        })
    })


    app.get('/google/profile', (req, res) => {
        googleAuthentifier.getProfile(req, function(profile) {
            res.send(`
                <h3>Hello ${profile.data.displayName}</h3>
            `);
        })
    })

    app.get('/office/mail', (req, res) => {
        officeAuthentifier.getMails(req, res, function(mail) {
            res.send(mail)
        })
    })

    app.get('/office/calendar', (req, res) => {
        officeAuthentifier.getCalendar(req, res, function(calendar) {
            res.send(calendar)
        })
    })

    app.get('/office/contact', (req, res) => {
        officeAuthentifier.getContacts(req, res, function(contacts) {
            res.send(contacts)
        })
    })

    app.get('/office/users', (req, res) => {
        officeAuthentifier.getContacts(req, res, function(contacts) {
            res.send(contacts)
        })
    })

}
