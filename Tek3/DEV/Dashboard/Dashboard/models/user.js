const mongoose = require('mongoose');

// we create a user schema

var meteoSchema = ({
	id: {
		type: Number
	},
	main: {
		type: String
	},
	description: {
		type: String
	},
	icon: {
		type: String
	}
})

var stockSchema = ({
	company: { type: String },
	date: { type: String },
	timeZone: { type: String },
	open: { type: Number },
	high: { type: Number },
	low: { type: Number },
	close: { type: Number },
	volume: { type: Number }
})

var wikiSchema = ({
	search: { type: String },
	name: { type: String },
	shortText: { type: String },
	url: { type: String }
})

var steamSchema = ({
	search: { type: String },
	success: { type: Boolean },
	name: { type: String },
	shortDesc: { type: String },
	picture: { type: String },
	price: { type: Number },
	currency: { type: String }
})

var countrySchema = ({
	search: { type: String },
	name: { type: String },
	capital: { type: String },
	population: { type: Number },
	language: { type: String },
	currencyName: { type: String },
	currencyCode: { type: String },
	flag: { type: String }
})

var serviceSchema = ({
	company: { type: Boolean },
	meteo: { type: Boolean },
	research: {type: Boolean}
})

var widgetSchema = ({
	meteo: { type: Boolean },
	stock: { type: Boolean },
	yt: { type: Boolean },
	wiki: { type: Boolean },
	steam: { type: Boolean },
	country: { type: Boolean },
	refresh_meteo: { type: Number },
	refresh_youtube: { type: Number },
	refresh_wiki: { type: Number },
	refresh_country: { type: Number },
	refresh_stock: { type: Number },
	refresh_steam: { type: Number },
	youtube: ({
		refresh: { type: Number },
		channel: {
			type: String,
			lowercase: true
		},
		subs: { type : Number },
		thumbnail: { type: String }
	})
})

const userSchema = new mongoose.Schema({
  username: {
		type: String,
		required: true
	},
	fullname: {
	  type: String,
	  required: true,
	},
	email: {
	  type: String,
	  required: true,
	  unique: true,
	  lowercase: true
	},
	city: {
		type: String,
		lowercase: false
	},
	temp: {
		type: String,
		lowercase: true
	},
	password: {
	  type: String,
	  required: true
	},
	weather: meteoSchema,
	stock: stockSchema,
	wiki: wikiSchema,
	services: serviceSchema,
	widgets: widgetSchema,
	steam: steamSchema,
	country: countrySchema
})

module.exports = userSchema;
