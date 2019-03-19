const bcrypt = require('bcrypt')

module.exports = function(sql) {

	// I can easily add the other services here
    var User = function(user) {
        this.username = user.username
        this.password = user.password
        this.email = user.email
		this.timer = 0
    }

    User.create = function create(newUser, callback) {
        if (!newUser.username || !newUser.password || !newUser.email) {
			callback(400, "Wrong parameters")
		} else {
			newUser.password = bcrypt.hashSync(newUser.password, 5)
			sql.query("SELECT 1 FROM users WHERE username = ?", newUser.username, function(err, res) {
				if (res[0])
					callback(400, "User already exists")
				else {
			        sql.query('INSERT INTO users set ?', newUser, function(err, res) {
			            if (err) {
			                callback(400, "Couldnt add the user to the database")
			            } else {
			                callback(200, "Success, new users ID is :" + res.insertId)
			            }
			        })
				}
			})
		}
    }

	User.createToken = function createToken(user, callback) {
		sql.query("SELECT * FROM users WHERE username = ?", user.username, function(err, res) {
			let oldToken = user.username.split(' ').join('_') + res[0].id
			var chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    		var token = '';
    		for (var i = 0; i < oldToken.length; i++) {
        		token += chars[Math.floor(Math.random() * chars.length)];
    		}
			sql.query('UPDATE users SET token = "' + token + '" WHERE username = ?', user.username, function(err, res) {
				if (err) {
					callback(err, 'Error while creating the token')
				} else {
					callback(null, token)
				}
			})
		})
	}

	User.loginOffice = function loginOffice(user, callback) {
		sql.query("SELECT * FROM users WHERE username = ?", user.username, function(err, res) {
			if (res[0]) {
				User.createToken(user, function(error, response) {
					if (error)
						callback(400)
					else
						callback(null, response)
				})
			} else {
				sql.query('INSERT INTO users set ?', user, function(err, res) {
					if (err) {
						callback(400, "Couldnt add the user to the database")
					} else {
						callback(200, "Success, new users ID is :" + res.insertId)
					}
				})
			}
		})
	}

	User.login = function login(user, callback) {
		if (!user.username || !user.password) {
			callback(400, "Wrong parameters")
		} else {
			sql.query("SELECT * FROM users WHERE username = ?", user.username, function(err, res) {
				if (res[0]) {
					if (bcrypt.compareSync(user.password, res[0].password))
						callback(null, res)
					else
						callback("Wrong password", 400)
				}
				else
					callback("User does not exist", 400)
			})
		}
	}

	User.getServices = function getServices(username, callback) {
		sql.query('SELECT * from users where username = ?', username, function (err, res) {
			if (err)
				return null
			else {
				let services = new Object()
				if (res[0].timer && res[0].date) {
					services['date'] = res[0].date
				}
				if (res[0].weather && res[0].city) {
					services['city'] = res[0].city
				}
				if (res[0].trends && res[0].subject) {
					services['subject'] = res[0].subject
				}
	//console.log(res)
				callback(services)
			}
		})
	}

	User.updateService = function updateService(username, service, value, callback) {
		//console.log(username, service, value)
		sql.query('UPDATE users SET ' + service + ' = "' + value + '" WHERE username = ?', username, function(err, res) {
			if (err) {
				console.log(err)
				callback(400)
			} else {
				callback(200)
			}
		})
	}

	User.subscribe = function subscribe(username, service, callback) {
		// Timer should be replaced by the list of services to be changed
		sql.query('UPDATE users SET ' + service + ' = 1 WHERE username = ?', username, function(err, res) {
			if (err) {
				callback(400)
			} else {
				callback(200)
			}
		})
	}

	User.unsubscribe = function unsubscribe(username, service, callback) {
		// Timer should be replaced by the list of services to be changed
		sql.query('UPDATE users SET ' + service + ' = 0 WHERE username = ?', username, function(err, res) {
			if (err) {
				callback(400)
			} else {
				callback(200)
			}
		})
	}

    User.showUsers = function showUsers() {
        sql.query('SELECT * from users where username = "philippe de-sousa-violante"', function(err, res) {
            if (err) {
                console.log('failure')
            } else {
                console.log('users: ', res)
            }
        })
    }

	User.getUsername = function getUsername(token, callback) {
		sql.query("SELECT * from users WHERE token = ?", token, function(err, res) {
			if (err) {
				callback ('Error while looking for the token', null)
			} else if (!res || res.length == 0) {
				callback('Wrong token!', null)
			} else {
				callback(null, res[0].username)
			}
		})
	}

	User.getEmail = function getEmail(token, callback) {
		sql.query("SELECT * from users WHERE token = ?", token, function(err, res) {
			if (err) {
				callback ('Error while looking for the token', null)
			} else if (!res || res.length == 0) {
				callback('Wrong token!', null)
			} else {
				callback(null, res[0].email)
			}
		})
	}

	User.delete = function remove(username, password, callback) {
		/// It will return OK even if the user doesn't exist
		sql.query("DELETE FROM users WHERE username = ? AND password = ?", [username, password], function (err, res) {
            if (err) {
                callback(400, "User does not exist")
			} else {
            	callback(200)
            }
        });
	}

    return User
}
