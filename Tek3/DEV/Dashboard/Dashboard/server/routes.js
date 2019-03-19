const express = require('express');
const http = require('http');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const session = require('express-session')
const shortid = require('shortid')
const bcrypt = require('bcrypt')
const fs = require('fs')
const WidgetsFunctions = require('./widget_handler')
const request = require('request')
const schemas = require('../models/about-json')
const aboutSchema = schemas.aboutSchema
const serviceSchema = schemas.serviceSchema
const widgetSchema = schemas.widgetSchema
var moment = require('moment')
let apiKeyWeather = '5d884ba40c58e0880a862ad05b592b4b'
let apiKeyStock = "PR9AWYSJ8I3OVI8E"

module.exports = function(app, Dashboard) {

    var Widgets = new WidgetsFunctions(Dashboard)

    app.get('/', (req, res) => {
        res.render('index')
    })

    app.get('/about.json', (req, res) => {
        about = getAboutJson(req)
        JSON.stringify(about);
        res.send(about)
    })

    app.post('/signup', (req, res) => {
        let {username, fullname, email, password} = req.body;
        let userData = {
            username,
            password: bcrypt.hashSync(password, 5),
            fullname,
            email
        };
        let newUser = new Dashboard(userData);
        newUser.save().then(error => {
            if (!error || error.code == undefined) {
                res.redirect('/')
            } else {
                if (error.code == 11000) {
                    return res.status(409).send('user already exists!')
                } else {
                    return res.status(500).send('error signing up user')
                }
            }
        })
    })

    app.post('/login', (req, res) => {
        let {username, password} = req.body;
        console.log(req.body)
        Dashboard.findOne({username: username}, 'username email password city temp weather services widgets wiki', (err, userData) => {
            if (!err && userData) {
                let passwordCheck = bcrypt.compareSync(password, userData.password);
                if (passwordCheck) {
                    req.session.user = {
                        email: userData.email,
                        username: userData.username,
                        id: userData._id,
                        temp: userData.temp,
                        city: userData.city,
                        weather: userData.weather,
                        services: userData.services,
                        widgets: userData.widgets,
                        wiki: userData.wiki
                    };
                    req.session.user.expires = new Date(
                        Date.now() + 3 * 24 * 3600 * 1000// session expires in 3 days
                    );
                    res.redirect('/services')
                } else {
                    res.status(401).send('incorrect password');
                }
            } else {
                // Rediriger sur '/' et mettre un message de loggin incorrect
                res.status(401).send('invalid login credentials')
            }
        })
    })
    
    app.use((req, res, next) => {
        if (req.session.user) {
            next();
        } else {
            // Rediriger sur '/' + message de login incorrect
            res.status(401).send('Authrization failed! Please login');
        }
    });

    app.post('/meteo', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteMeteo(req.session.user)
            res.redirect('dashboard')
        } else {
            let city = req.body.city;
            if (req.body.refresh)
                req.session.user.widgets.refresh_meteo = convertTimer(req.body.refresh)
            let url = `http://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${apiKeyWeather}`
            request(url, function (err, response, body) {
                if(err){
                    res.redirect('dashboard')
                } else {
                    let weather = JSON.parse(body)
                    if (weather.main == undefined){
                        res.redirect('dashboard')
                    } else {
                        req.session.user.city = city
                        req.session.user.temp = weather.main.temp
                        req.session.user.weather = weather.weather[0]
                        req.session.user.widgets.meteo = true;
                        Widgets.updateDashboard(req.session.user)
                        res.redirect('dashboard')
                    }
                }
            });
        }
    })

    app.post('/youtube', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteYoutube(req.session.user)
            res.redirect('dashboard')
        } else {
            var channel = req.body.channel
            req.session.user.widgets.yt = true
            if (req.body.refresh)
                req.session.user.widgets.youtube.refresh = convertTimer(req.body.refresh)
            Widgets.getYoutubeChannel(req.session.user, channel, res, function (callback) {
                res.redirect('dashboard')
            })
        }
    })

    app.post('/wiki', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteWiki(req.session.user)
            res.redirect('dashboard')
        } else {
            req.session.user.widgets.wiki = true
            req.session.user.wiki = {};
            req.session.user.wiki.search = req.body.search;
            Widgets.getWikipedia(req.session.user, function (callback) {
                res.redirect('dashboard')
            })
        }
    })

    app.post('/steam', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteSteam(req.session.user)
            res.redirect('dashboard')
        } else {
            req.session.user.widgets.steam = true
            req.session.user.steam = {};
            req.session.user.steam.search = req.body.search;
            Widgets.getSteam(req.session.user, function (callback) {
                res.redirect('dashboard')
            })
        }
    })

    app.post('/country', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteCountry(req.session.user)
            res.redirect('dashboard')
        } else {
            req.session.user.widgets.country = true
            req.session.user.country = {};
            req.session.user.country.search = req.body.search;
            Widgets.getCountry(req.session.user, function (callback) {
                res.redirect('dashboard')
            })
        }
    })

    app.get('/services', (req, res) => {
            res.render('services');
    })

    app.post('/dashboard', (req, res) => {
        if (!req.body.services || req.body.services.includes("meteo") || req.body.services.includes("stock")
        || req.body.services.includes("research")) {
            req.session.user.services.meteo = false
            req.session.user.services.stock = false
            req.session.user.services.research = false
        }
        if (req.body.services && req.body.services.includes("meteo"))
            req.session.user.services.meteo = true;
        if (req.body.services && req.body.services.includes("stock"))
            req.session.user.services.stock = true;
        if (req.body.services && req.body.services.includes("research"))
            req.session.user.services.research = true;
        if (!req.session.widgets)
            req.session.widgets = []
        Widgets.updateDashboard(req.session.user)
        res.redirect('./dashboard')
    })

    app.post('/stock', (req, res) => {
        if (req.body.constructor === Object && Object.keys(req.body).length === 0) {
            Widgets.deleteStock(req.session.user)
            res.redirect('dashboard')
        } else {
            let company = req.body.company
            let url = `https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=${company}&interval=5min&apikey=${apiKeyStock}`
            req.session.user.stock = {};
            req.session.user.widgets.stock = true
            request(url, (err, response, body) => {
                if (!err) {
                    let stock = JSON.parse(body)
                    let timeSerie5 = stock["Time Series (5min)"];
                    for (object in timeSerie5) {
                        var metaData = stock["Meta Data"];
                        req.session.user.stock.company = metaData["2. Symbol"];
                        req.session.user.stock.date = JSON.stringify(object);
                        req.session.user.stock.timeZone = metaData["6. Time Zone"];
                        var stats = timeSerie5[object];
                        req.session.user.stock.open = stats["1. open"];
                        req.session.user.stock.high = stats["2. high"];
                        req.session.user.stock.low = stats["3. low"];
                        req.session.user.stock.close = stats["4. close"];
                        req.session.user.stock.volume = stats["5. volume"];
                        break; // I only need the first one (Object.getKeys in horrible)
                        Widgets.updateDashboard(req.session.user)
                        res.redirect('dashboard')
                    }
                }
                res.redirect("dashboard")
            });
        }
    })

    app.get('/dashboard', (req, res) => {
        Widgets.refreshAll(req.session.user)
        res.render('dashboard', {user: req.session.user});
    })

    app.all('/logout', (req, res) => {
        delete req.session.user; // any of these works
        res.redirect('/')
    })

}

function convertTimer(timer) {
    if (timer === '5 minutes')
        return (60000 * 5)
    if (timer === '10 minutes')
        return (60000 * 10)
    if (timer === '30 minutes')
        return (60000 * 30)
    if (timer === '1 hour')
        return (60000 * 60)
    if (timer === '1 hour')
        return (60000 * 60 * 3)
}

function getAboutJson (req) {

    about = aboutSchema
    about.client.host = req.connection.remoteAddress
    about.server.current_time = (moment().unix())
    var weatherService = JSON.parse(JSON.stringify(serviceSchema));
    weatherService.name = "weather"
    weatherService.widgets[0].name = "city_temperature"
    weatherService.widgets[0].description = "Affichage de la temperature pour une ville"
    weatherService.widgets[0].params[0].name = "city"
    weatherService.widgets[0].params[0].type = "string"
    var stockService = JSON.parse(JSON.stringify(serviceSchema));
    stockService.name = "stock"
    stockService.widgets[0].name = "stock"
    stockService.widgets[0].description = "Affichage de la valeur d'une action pour une entreprise"
    stockService.widgets[0].params[0].name = "company"
    stockService.widgets[0].params[0].type = "string"
    var researchService = JSON.parse(JSON.stringify(serviceSchema))
    researchService.name = "research"
    var youtubeWidget = JSON.parse(JSON.stringify(widgetSchema))
    youtubeWidget.name = "Youtube"
    youtubeWidget.description = "Affichage du nombre d'abonnés pour une chaîne"
    youtubeWidget.params[0].name = "channel"
    youtubeWidget.params[0].type = "string"
    var wikipediaWidget = JSON.parse(JSON.stringify(widgetSchema))
    wikipediaWidget.name = "Wikipedia"
    wikipediaWidget.description = "Affichage d'une page wikipedia"
    wikipediaWidget.params[0].name = "search"
    wikipediaWidget.params[0].type = "string"
    var steamWidget = JSON.parse(JSON.stringify(widgetSchema))
    steamWidget.name = "Steam"
    steamWidget.description = "Affichage du prix d'un jeu steam selon son ID"
    steamWidget.params[0].name = "id"
    steamWidget.params[0].type = "string"
    var countryWidget = JSON.parse(JSON.stringify(widgetSchema))
    countryWidget.name = "Country"
    countryWidget.description = "Affichage des informations sur un pays"
    countryWidget.params[0].name = "country"
    countryWidget.params[0].type = "string"
    researchService.widgets[0] = youtubeWidget
    researchService.widgets.push(wikipediaWidget, steamWidget, countryWidget)
    about.server.services[0] = weatherService
    about.server.services.push(stockService, researchService)

    return about
}
