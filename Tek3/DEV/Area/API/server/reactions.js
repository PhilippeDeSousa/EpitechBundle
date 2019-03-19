const nodemailer = require('nodemailer')

module.exports = function() {

	var Reactions = function(reaction) {
		this.name = reaction.name
		this.id = reaction.id
	}

	Reactions.sendEmail = function sendEmail(content, callback) {
		var transporter = nodemailer.createTransport({
			service: 'gmail',
			auth: {
				user: 'epicare.epitech@gmail.com',
				pass: 'epicare2018'
			}
		})

		var mailOptions = {
			from: 'epicare.epitech@gmail.com',
			to: content.email,
			subject: '[AREA] ' + content.subject,
			text: content.content
		}

		transporter.sendMail(mailOptions, function(error, info){
			if (error) {
				console.log(error);
				callback(400)
			} else {
				callback(200)
			}
		})
	}


	Reactions.react = function react(username, name, content, User, reset, callback) {
		console.log('Reacting')
		if (name == "email") {
	  		this.sendEmail(content, callback)
			User.updateService(username, reset.service, reset.value, callback)
		} else if (name == "notif") {
			User.updateService(username, reset.service, reset.value, callback)
			callback(content)
	  		//this.send??(content, callback)
		}
	}

	return Reactions
}
