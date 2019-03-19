const cookieParser = require('cookie-parser')
const logger = require('morgan')
const express = require('express')
const bodyParser = require('body-parser')
const session = require('express-session')
const router = require('./server/router.js')
const mysql = require('mysql')
const PORT = 8080

app = express()

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*")
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS')
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
    next()
})

const con = mysql.createConnection({
    host: "epicare.fr",
    user: "area",
    password: "password",
    database: "area"
})

con.connect(function (err) {
    if (!err) {
        console.log("Database is connected ...")
    } else {
        console.log("Error connecting database ...")
    }
})

require('dotenv').config()

app.use(logger('dev'))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(cookieParser())

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended: false}))
app.use(session({
    secret: 'raysources-secret-19890913007',
    resave: true,   
    saveUninitialized: true
}))

router(app, con)

app.listen(PORT, () => {
    console.log('Server is running on port ' + PORT)
})
