var authHelper = require('./officeHelper')
var graph = require('@microsoft/microsoft-graph-client')
const jwt = require('jsonwebtoken');

/* GET home page. */

function officeAuthentifier (app, User) {

    var officeAuthentifier = this

    var oauth2return = ""

    officeAuthentifier.auth = function(req, res, callback) {
        let params = { title: 'Home', active: { home: true } }

        const accessToken = req.cookies.graph_access_token
        const userName = req.cookies.graph_user_name

        if (accessToken && userName) {
            params.user = userName
            params.debug = `User: ${userName}\nAccess Token: ${accessToken}`
        } else {
            params.signInUrl = authHelper.getAuthUrl()
            params.debug = params.signInUrl
        }
        callback(params)
    }

    officeAuthentifier.authOffice = async function(req, res, callback) {
        let params = { title: 'Home', active: { home: true } }

        if (req.query.return)
            oauth2return = req.query.return

        const accessToken = req.cookies.graph_access_token
        const userName = req.cookies.graph_user_name

        if (accessToken && userName) {
            params.user = userName
            params.debug = `User: ${userName}\nAccess Token: ${accessToken}`
        } else {
            params.signInUrl = authHelper.getAuthUrl()
            params.debug = params.signInUrl
        }
        callback(params)
    }

    officeAuthentifier.getMails = async function(req, res, callback) {
        let parms = { title: 'Inbox', active: { inbox: true } }

        const accessToken = await authHelper.getAccessToken(req.cookies, res)
        const userName = req.cookies.graph_user_name

        if (accessToken && userName) {
            parms.user = userName
            const client = graph.Client.init({
                authProvider: (done) => {
                    done(null, accessToken)
                }
            })

            try {
            // Get the 10 newest messages from inbox
                const result = await client
                .api('/me/mailfolders/inbox/messages')
                .top(10)
                .select('subject,from,receivedDateTime,isRead')
                .orderby('receivedDateTime DESC')
                .get()

                parms.messages = result.value
                callback(parms)
            } catch (err) {
                parms.message = 'Error retrieving messages'
                parms.error = { status: `${err.code}: ${err.message}` }
                parms.debug = JSON.stringify(err.body, null, 2)
                callback(parms)
            }
        } else {
            callback('user is not logged in')
        }
    }

    officeAuthentifier.getCalendar = async function(req, res, callback) {
        let parms = { title: 'Calendar', active: { calendar: true } }

        const accessToken = await authHelper.getAccessToken(req.cookies, res)
        const userName = req.cookies.graph_user_name

        if (accessToken && userName) {
            parms.user = userName
            const client = graph.Client.init({
                authProvider: (done) => {
                    done(null, accessToken)
                }
            })

            // Set start of the calendar view to today at midnight
            const start = new Date(new Date().setHours(0,0,0))
            // Set end of the calendar view to 7 days from start
            const end = new Date(new Date(start).setDate(start.getDate() + 7))

            try {
            // Get the first 10 events for the coming week
                const result = await client
                .api(`/me/calendarView?startDateTime=${start.toISOString()}&endDateTime=${end.toISOString()}`)
                .top(10)
                .select('subject,start,end,attendees')
                .orderby('start/dateTime DESC')
                .get()

                parms.events = result.value
                callback(parms)
            } catch (err) {
                parms.message = 'Error retrieving events'
                parms.error = { status: `${err.code}: ${err.message}` }
                parms.debug = JSON.stringify(err.body, null, 2)
                callback(parms)
            }

        } else {
            // Redirect to home
            callback('user is not logged in')
        }
    }

    officeAuthentifier.getContacts = async function(req, res, callback) {
        let parms = { title: 'Contacts', active: { contacts: true } }

        const accessToken = await authHelper.getAccessToken(req.cookies, res)
        const userName = req.cookies.graph_user_name

        if (accessToken && userName) {
            parms.user = userName

            // Initialize Graph client
            const client = graph.Client.init({
            authProvider: (done) => {
                done(null, accessToken)
            }
            })

            try {
            // Get the first 10 contacts in alphabetical order
            // by given name
            const result = await client
            .api('/me/contacts')
            .top(10)
            .select('givenName,surname,emailAddresses')
            .orderby('givenName ASC')
            .get()

            parms.contacts = result.value
            callback(parms)
            } catch (err) {
                parms.message = 'Error retrieving contacts'
                parms.error = { status: `${err.code}: ${err.message}` }
                parms.debug = JSON.stringify(err.body, null, 2)
                callback(parms)
            }

        } else {
            callback('user is not logged')
        }
    }

    app.use('/auth/office/oauthCallback', async function(req, res) {
        const code = req.query.code
        if (code) {
			let fullToken
            let token
            try {
                fullToken = await authHelper.getTokenFromCode(code, res)
				let decoded = jwt.decode(fullToken.token.id_token)
				User.loginOffice({username: decoded.name, email: decoded.preferred_username, office_token: fullToken.token.access_token}, function(err, resp) {
		            if (oauth2return) {
		                res.redirect(oauth2return + resp)
		            } else {
		                res.sendStatus(200)
		            }
				})
            } catch (error) {
				res.status(400).send(error)
            }
        } else {
            res.status(400).send(error)
        }
    })

    app.get('/auth/office/signout', function(req, res) {
        authHelper.clearCookies(res)
        res.sendStatus(200)
    })

    return officeAuthentifier
}

module.exports = officeAuthentifier
