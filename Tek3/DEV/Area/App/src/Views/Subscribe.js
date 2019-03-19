import React, { Component } from 'react';
import 'bootstrap/dist/css/bootstrap.css';
import 'react-web-notification/lib/components/Notification';
import $ from 'jquery';

export default class Index extends Component {

    constructor() {
        super()
        this.state = {
            token: 'tanguy71',
            isTimer: false,
            isWeather: false,
            timerDate: '0000-00-00 00:00:00',
            weatherCity: '',
            nb_displays: 0,
            sendTimerMail: false,
            sendWeatherMail: false,
            isTrends: false,
            enableTrends: false,
            trendsSubject: '',
            setTrendsMail: false,
            fireRedirect: false
        }
        this.callSubscribe = this.callSubscribe.bind(this);
        this.enableTimer = this.enableTimer.bind(this);
        this.enableTimerMail = this.enableTimerMail.bind(this);
        this.enableWeather = this.enableWeather.bind(this);
        this.enableWeatherMail = this.enableWeatherMail.bind(this);
        this.setTimerDate = this.setTimerDate.bind(this);
        this.setWeatherCity = this.setWeatherCity.bind(this);
        this.setTimerService = this.setTimerService.bind(this);
        this.setWeatherService = this.setWeatherService.bind(this);
        this.setTrendsService = this.setTrendsService.bind(this);
        this.componentDidMount = this.componentDidMount.bind(this);
    }

    async componentDidMount() {
        var url = window.location.href.split('/subscribe/');
        this.token = url[1];
        this.nb_displays = 0;
        try {
            setInterval(async () => {
                fetch('http://localhost:8080/notifs?token=' + this.token, {
                    method: 'get',
                    headers: { 'Content-type': 'application/x-www-form-urlencoded' }
                })
                    .then((res) => {
                        if (res.status === 200) {
                            console.log(this.nb_displays)
                            if (this.nb_displays < 1) {
                                alert("Timer is over !")
                                this.nb_displays = 1;
                                console.log(this.nb_displays)
                            }
                        } else if (res.status === 201) {

                        }
                    })
            }, 3000);
        } catch (e) {
            console.log(e);
        }
    }

    callSubscribe = async (e, service) => {
        e.preventDefault()
        fetch('http://localhost:8080/subscribe?token=' + this.token, {
            method: 'post',
            body: 'service=' + service,
            headers: { 'Content-type': 'application/x-www-form-urlencoded' }
        })
            .then((res) => {
                if (res.ok) {
                    return res
                } else {
                    let errorMessage = 'error', error = new Error(errorMessage)
                    throw (error)
                }
            })
        e.preventDefault()
        if (service === "weather") {
            fetch('http://localhost:8080/add?token=' + this.token, {
                method: 'post',
                body: 'service=' + service + '&city=' + this.weatherCity,
                headers: { 'Content-type': 'application/x-www-form-urlencoded' }
            })
                .then((res) => {
                    if (res.ok) {
                        return res
                    } else {
                        let errorMessage = 'error', error = new Error(errorMessage)
                        throw (error)
                    }
                })
        } else if (service === "timer") {
            fetch('http://localhost:8080/add?token=' + this.token, {
                method: 'post',
                body: 'service=' + service + '&date=' + this.timerDate,
                headers: { 'Content-type': 'application/x-www-form-urlencoded' }
            })
                .then((res) => {
                    if (res.ok) {
                        return res
                    } else {
                        let errorMessage = 'error', error = new Error(errorMessage)
                        throw (error)
                    }
                })
        } else if (service === "trends") {
            fetch('http://localhost:8080/add?token=' + this.token, {
                method: 'post',
                body: 'service=' + service + '&subject=' + this.trendsSubject,
                headers: { 'Content-type': 'application/x-www-form-urlencoded' }
            })
                .then((res) => {
                    if (res.ok) {
                        return res
                    } else {
                        let errorMessage = 'error', error = new Error(errorMessage)
                        throw (error)
                    }
                })

        }
    }


    //Timer part

    enableTimer(event) {
        if (event.target.checked) {
            this.isTimer = true;
        } else {
            this.isTimer = false;
            this.sendTimerMail = false;
        }
    }

    setTimerDate(event) {
        this.timerDate = event.target.value;
        var tmp = this.timerDate.split('T');
        this.timerDate = tmp[0] + ' ' + tmp[1] + ':00';
    }

    enableTimerMail(event) {
        if (event.target.checked && this.isTimer) {
            this.sendTimerMail = true;
        } else {
            this.sendTimerMail = false;
        }
    }

    setTimerService(event) {
        // alert("Service timer is " + this.isTimer);
        // alert("mail status is " + this.sendTimerMail);
        // alert("timer date is " + this.timerDate);
        var url = window.location.href.split('/subscribe/');
        this.token = url[1];
        if (this.isTimer && this.timerDate && this.sendTimerMail) {
            alert("You will receive an email alert at " + this.timerDate);
        } else if (this.isTimer && this.timerDate) {
            alert("You will receive an alert at " + this.timerDate);
        } else {
            alert("Please subscribe and/or enter a date")
            return;
        }
        this.callSubscribe(event, "timer");
        //TODO: add unsubscribe
    }

    //Weather part

    enableWeather(event) {
        if (event.target.checked) {
            this.isWeather = true;
        } else {
            this.isWeather = false;
            this.sendWeatherMail = false;
        }
    }

    setWeatherCity(event) {
        this.weatherCity = event.target.value;
    }

    enableWeatherMail(event) {
        if (event.target.checked && this.isWeather) {
            this.sendWeatherMail = true;
        } else {
            this.sendWeatherMail = false;
        }
    }
    setWeatherService(event) {
        // alert("Service weather is " + this.isWeather);
        // alert("mail status is " + this.sendWeatherMail);
        // alert("weather city is " + this.weatherCity);
        var url = window.location.href.split('/subscribe/');
        this.token = url[1];
        if (this.isWeather && this.weatherCity && this.sendWeatherMail) {
            alert("You will receive an email weather alert for " + this.weatherCity);
        } else if (this.isWeather && this.weatherCity) {
            alert("You will receive a weather alert for " + this.weatherCity);
        } else {
            alert("Please subscribe and/or enter a city");
            return;
        }
        this.callSubscribe(event, "weather");
        //TODO: add unsubscribe
    }

    //Service part

    enableTrends(event) {
        if (event.target.checked) {
            this.isTrends = true;
        } else {
            this.isTrends = false;
            this.sendTrendsMail = false;
        }
    }

    setTrendsSubject(event) {
        this.trendsSubject = event.target.value;
    }

    setTrendsService(event) {
        // alert("Service trends is " + this.isTrends);
        // alert("mail status is " + this.sendTrendsMail);
        // alert("weather city is " + this.trendsSubject);
        var url = window.location.href.split('/subscribe/');
        this.token = url[1];
        if (this.isTrends && this.trendsSubject && this.sendTrendsMail) {
            alert("You will receive mail trends alerts for this subject : " + this.trendsSubject);
        } else if (this.isTrends && this.trendsSubject) {
            alert("You will receive trends alerts for this subject : " + this.trendsSubject);
        } else {
            alert("Please subscribe and/or enter a subject");
            return;
        }
        this.callSubscribe(event, "trends");
        //TODO: add unsubscribe
    }


    render() {

        $(document).ready(function () {
            $('ul.tabs li').click(function () {
                var tab_id = $(this).attr('data-tab');

                $('ul.tabs li').removeClass('current');
                $('.tab-content').removeClass('current');

                $(this).addClass('current');
                $("#" + tab_id).addClass('current');
            });

            $("#datepicker").on("click", function () {
                $("#datepicker").datepicker();
            });

        });

        return (
            <div>
                <h2 style={{ textAlign: "center" }}>Please choose your services</h2>
                {
                    <div id="container">
                        <ul class="tabs">
                            <li class="tab-link current" data-tab="tab-1">Timer</li>
                            <li class="tab-link" data-tab="tab-2">Weather</li>
                            <li class="tab-link" data-tab="tab-3">Trends</li>
                        </ul>

                        <div id="tab-1" class="login tab-content current">
                            <input type="checkbox" name="subscribe" value="timer" onClick={(event) => { this.enableTimer(event) }} /> Subscribe to this service<br></br>
                            {/* <input type="checkbox" name="email" value="timer-email" onClick={(event) => { this.enableTimerMail(event) }} /> Receive an email on the specified date<br></br> */}
                            <form>
                                <p style={{ display: "inline-block" }}>Please pick a date</p>
                                <input type="datetime-local" name="bdaytime" tyle={{ display: "inline-block" }} onChange={(event) => { this.setTimerDate(event) }} />
                            </form>
                            <div class="form-section btn-container">
                                <input type="submit" value="Save changes" onClick={(event) => { this.setTimerService(event) }} />
                            </div>
                        </div>

                        <div id="tab-2" class="register tab-content">
                            <input type="checkbox" name="subscribe" value="weather" onClick={(event) => { this.enableWeather(event) }} /> Subscribe to this service<br></br>
                            {/* <input type="checkbox" name="email" value="weatheremail" onClick={(event) => { this.enableWeatherMail(event) }} /> Receive an email when it's raining<br></br> */}
                            <form>
                                <p style={{ display: "inline-block" }}>Please enter a city</p>
                                <input style={{ display: "inline-block" }} type="text" name="city" onChange={(event) => { this.setWeatherCity(event) }} />
                            </form>
                            <div class="form-section btn-container">
                                <input type="submit" value="Save changes" onClick={(event) => { this.setWeatherService(event) }} />
                            </div>
                        </div>

                        <div id="tab-3" class="register tab-content">
                            <input type="checkbox" name="subscribe" value="weather" onClick={(event) => { this.enableTrends(event) }} /> Subscribe to this service<br></br>
                            {/* <input type="checkbox" name="email" value="weatheremail" onClick={(event) => { this.enableWeatherMail(event) }} /> Receive an email when it's raining<br></br> */}
                            <form>
                                <p style={{ display: "inline-block" }}>Please enter a subject</p>
                                <input style={{ display: "inline-block" }} type="text" name="subject" onChange={(event) => { this.setTrendsSubject(event) }} />
                            </form>
                            <div class="form-section btn-container">
                                <input type="submit" value="Save changes" onClick={(event) => { this.setTrendsService(event) }} />
                            </div>
                        </div>
                    </div>
                }
            </div>
        )
    }
}
