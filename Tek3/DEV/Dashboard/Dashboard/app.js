const express = require('express');
const app = express();
const http = require('http');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const session = require('express-session')
const shortid = require('shortid')
const bcrypt = require('bcrypt')
const path = require('path')
const WidgetsFunctions = require('./server/widget_handler')
const fs = require('fs');

const PORT = 8080

mongoose.connect('mongodb://mongo:27017/dashboard', {
	useNewUrlParser: true
})
.catch((err) => {
	console.log("Failed to connect to the mongod docker container, connecting to local db");
	mongoose.connect('mongodb://localhost:27017/dashboard', {
		useNewUrlParser: true
	})
  .catch((err) => {
      console.error("ERROR: mongoDB not running\n" + err.stack)
      process.exit(1)
        })
});

const User = require('./models/user')

mongoose.Promise = global.Promise;

var Dashboard = mongoose.model('Dashboard', User)

var Widgets = new WidgetsFunctions(Dashboard)
Widgets.getAllUsers()

app.use(express.static(path.join(__dirname, 'public')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(
	session({
		secret: "iy98hcbh489n38984y4h498",
		resave: true,
		saveUninitialized: false
	})
);

app.set('views', __dirname + '/views/')
app.set('view engine', 'ejs')


var setRoutes = require('./server/routes.js')

setRoutes(app, Dashboard)

app.listen(PORT, () => {
	console.log('Listening on port ' + PORT);
});


