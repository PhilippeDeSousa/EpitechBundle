var express = require('express')
var Session = require('express-session')
var {google} = require('googleapis')
var plus = google.plus('v1')
var OAuth2 = google.auth.OAuth2
const ClientId = "113342332437-1tfnmhi4og2a7p174vaf66o4fa12qafc.apps.googleusercontent.com"
const ClientSecret = "Xh0KjfMwsFTsp8n2tVGaTxoM"
const RedirectionUrl = "http://localhost:8080/auth/google/oauthCallback"

function getOAuthClient () {
    return new OAuth2(ClientId ,  ClientSecret, RedirectionUrl)
}

function getAuthUrl () {
    var oauth2Client = getOAuthClient()
    // generate a url that asks permissions for Google+ and Google Calendar scopes
    var scopes = [
    'https://www.googleapis.com/auth/plus.me'
    ]

    var url = oauth2Client.generateAuthUrl({
        access_type: 'offline',
        scope: scopes // If you only need one scope you can pass it as string
    })

    return url
}

function googleAuthentifier (app) {

    var googleAuthentifier = this
    var googleAuthReturn = ""
    
    app.use("/auth/google/oauthCallback", function (req, res) {
        let oauth2Client = getOAuthClient()
        let session = req.session
        let code = req.query.code
        oauth2Client.getToken(code, function(err, tokens) {
        // Now tokens contains an access_token and an optional refresh_token. Save them.
        if(!err) {
            oauth2Client.setCredentials(tokens)
            session["tokens"] = tokens
            console.log("I should redirect him to" + googleAuthReturn)
            if (googleAuthReturn)
                res.redirect(googleAuthReturn)
            else
                res.sendStatus(200)
        }
        else
            res.sendStatus(400)
        })
    })

    googleAuthentifier.getProfile = function(req, callback) {
        var oauth2Client = getOAuthClient()
        oauth2Client.setCredentials(req.session["tokens"])
    
        var p = new Promise(function (resolve, reject) {
            plus.people.get({ userId: 'me', auth: oauth2Client }, function(err, response) {
                resolve(response || err)
            })
        }).then(function (data) {
            callback(data)
        })
    }
    
    googleAuthentifier.authGoogle = function(req, res, callback) {
        if (req.query.return)
            googleAuthReturn = req.query.return
        var url = getAuthUrl()
        callback(url)
    }

    return googleAuthentifier
}

module.exports = googleAuthentifier
