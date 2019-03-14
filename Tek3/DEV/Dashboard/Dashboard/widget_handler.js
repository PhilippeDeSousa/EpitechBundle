const request = require('request')
const bodyParser = require('body-parser')
let apiKeyWeather = '5fa3134061e8900ec80084f855ea641a'
let apiKeyStock = "PR9AWYSJ8I3OVI8E"
let apiKeyYoutube = 'AIzaSyC-DmOx1UANbNJrb_DI54EnXCX3tkU_jt0'
var SCOPES = ['https://www.googleapis.com/auth/youtube.readonly'];
var TOKEN_DIR = (process.env.HOME || process.env.HOMEPATH ||
    process.env.USERPROFILE) + '/.credentials/';
var TOKEN_PATH = TOKEN_DIR + 'youtube-nodejs-quickstart.json';
var readline = require('readline');
var {google} = require('googleapis');
var OAuth2 = google.auth.OAuth2;
const fs = require('fs')

/* TODO:    Bouton pour add les widgets des différents services
            Timer sur les différents widgets (cronJob ou front)
            Faire le about.json
            Bouton suppression d'un widget
*/
function WidgetFunctions(Dashboard) {

    var Widgets = this

    Widgets.getAllUsers = function () {
        Dashboard.find({}, function(err, users) {
            users.forEach(function (user) {
                Widgets.refreshMeteo(user)
                Widgets.refreshStock(user)
                Widgets.updateDashboard(Dashboard, user)
            })
        })
    }

    Widgets.refreshAll = function (curUser) {
        Dashboard.findById(curUser.id, function(err, user) {
            if (user.widgets.meteo == true && user.widgets.refresh_meteo > 10)
                myVar = setInterval(Widgets.refreshMeteo, user.widgets.refresh_meteo, user)
            if (user.services.meteo == true)
                Widgets.refreshMeteo(user)
            Widgets.refreshStock(user)
            Widgets.updateDashboard(Dashboard, user)
        })
    }

    /*Widgets.addWidgetMeteo = function (curUser, city, weather) {
        var newMeteo = widgetSchema
        newMeteo.name = 'meteo'
        newMeteo.weather = weather.weather[0]
        newMeteo.city = city
        newMeteo.temp = weather.main.temp
        if (!curUser.widget)
            curUser.widget = [widgetSchema]
        curUser.widget.push(newMeteo)
    }*/

    Widgets.getYoutubeChannel = function(user, channame, callback) {
        fs.readFile('client_secret.json', function processClientSecrets(err, content) {
            if (err) {
              console.log('Error loading client secret file: ' + err);
              return;
            }
            var oldname = user.widgets.youtube.channel
            user.widgets.youtube.channel = channame
            authorize(JSON.parse(content), getChannel, user, function (channel) {
                if (channel) {
                    user.widgets.youtube.subs = channel.subs
                    user.widgets.youtube.thumbnail = channel.thumbnail.default.url
                    console.log(channel.thumbnail.surl)
                    Widgets.updateDashboard(user)
                } else {
                    user.widgets.youtube.channel = oldname
                }
                callback();
            });
          });
    }

    Widgets.refreshMeteo = function (user) {
        if (user.city) {
            let city = user.city
            let url = `http://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${apiKeyWeather}`
            request(url, function (err, response, body) {
                if (!err) {
                    let weather = JSON.parse(body)
                    if (weather.main != undefined)
                        user.weather = weather.weather[0]
                }
            })
        }
    }

    Widgets.deleteYoutube = function (user) {
        user.widgets.yt = false
        Widgets.updateDashboard(user)
    }

    Widgets.deleteMeteo = function (user) {
        user.widgets.meteo = false;
        Widgets.updateDashboard(user)
    }

    Widgets.deleteStock = function (user) {
        user.widgets.stock = false;
        Widgets.updateDashboard(user)
    }

    Widgets.refreshStock = function (user) {
        user.stock = {};
        if (user.company) {
            let company = user.company
            let url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=${company}&interval=5min&apikey=${apiKeyStock}"
            request(url, (err, response, body) => {
                if (!err) {
                    let stock = JSON.parse(body)
                    let timeSerie5 = stock["Time Series (5min)"];
                    for (object in timeSerie5) {
                        var metaData = stock["Meta Data"];
                        user.stock.company = metaData["2. Symbol"];
                        user.stock.date = JSON.stringify(object);
                        user.stock.timeZone = metaData["6. Time Zone"];
                        var stats = timeSerie5[object];
                        user.stock.open = stats["1. open"];
                        user.stock.high = stats["2. high"];
                        user.stock.low = stats["3. low"];
                        user.stock.close = stats["4. close"];
                        user.stock.volume = stats["5. volume"];
                        break; // I only need the first one (Object.getKeys in horrible)
                    }
                }
            });
        }
    }

    Widgets.refreshMap = function (user) {
        user.map = {};
    }

    Widgets.updateDashboard = function (newUser) {
        Dashboard.findById(newUser.id, function(err, user) {
            if (err) {
                console.log(err)
            } else {
                var keys = ['city', 'temp', 'weather', 'services', 'widgets']
                copyObjectKeys(newUser, user, keys)
                if (user) {
                    user.save(function(error) {
                        if (error) {
                            console.log('error while saving the new guy')
                        } else {
                            console.log('user', user.username, 'was correctly saved')
                        }
                    })
                }
            }
        })
    }
}

function copyObjectKeys (source, destination, keys) {
    keys.forEach(function (key) {
        if (source[key])
            destination[key] = source[key]
    })
}

function authorize(credentials, callback, user, callchan) {
    var clientSecret = credentials.installed.client_secret;
    var clientId = credentials.installed.client_id;
    var redirectUrl = credentials.installed.redirect_uris[0];
    var oauth2Client = new OAuth2(clientId, clientSecret, redirectUrl);
  
    // Check if we have previously stored a token.
    fs.readFile(TOKEN_PATH, function(err, token) {
      if (err) {
        getNewToken(oauth2Client, callback, user, callchan);
      } else {
        oauth2Client.credentials = JSON.parse(token);
        callback(oauth2Client, user, callchan);
      }
    });
}  

function getNewToken(oauth2Client, callback, user, callchan) {
    var authUrl = oauth2Client.generateAuthUrl({
      access_type: 'offline',
      scope: SCOPES
    });
    console.log('Authorize this app by visiting this url: ', authUrl);
    var rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout
    });
    rl.question('Enter the code from that page here: ', function(code) {
      rl.close();
      oauth2Client.getToken(code, function(err, token) {
        if (err) {
          console.log('Error while trying to retrieve access token', err);
          return;
        }
        oauth2Client.credentials = token;
        storeToken(token);
        callback(oauth2Client, user, callchan);
      });
    });
}  

function storeToken(token) {
    try {
      fs.mkdirSync(TOKEN_DIR);
    } catch (err) {
      if (err.code != 'EEXIST') {
        throw err;
      }
    }
    fs.writeFile(TOKEN_PATH, JSON.stringify(token), (err) => {
      if (err) throw err;
      console.log('Token stored to ' + TOKEN_PATH);
    });
    console.log('Token stored to ' + TOKEN_PATH);
}  

function getChannel(auth, user, callchan) {
    var service = google.youtube('v3');
    service.channels.list({
      auth: auth,
      part: 'snippet,contentDetails,statistics',
      forUsername: user.widgets.youtube.channel
    }, function(err, response) {
      if (err) {
        console.log('The API returned an error: ' + err);
        return;
      }
      var channels = response.data.items;
      if (channels.length == 0) {
        callchan(null)
      } else {
        var channel_infos = {
            subs: channels[0].statistics.subscriberCount,
            thumbnail: channels[0].snippet.thumbnails
        }
        callchan(channel_infos)
      }
    });
}


module.exports = WidgetFunctions
