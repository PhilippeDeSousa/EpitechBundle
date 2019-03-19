import React, { Component } from 'react';
import 'bootstrap/dist/css/bootstrap.css';
import '../Public/Index.scss';
import { Redirect } from 'react-router';
import $ from 'jquery';

export default class Index extends Component {

	constructor() {
		super()
		this.state = {
			name: 'hello world',
			username: 'philippe',
			password: '1234',
			token: '',
			email: 'email@gmail.com',
			officeUrl: '',
			fireRedirect: false
		}
		this.handleChange = this.handleChange.bind(this);
		this.changePassword = this.changePassword.bind(this);
		this.changeEmail = this.changeEmail.bind(this);
		this.callToken = this.callToken.bind(this);
		this.callSignup = this.callSignup.bind(this);
		this.officeLogin = this.officeLogin.bind(this);
	}

	componentDidMount() {
        this.officeLogin()
    }

	callToken = async (e) => {
		e.preventDefault()
		fetch('http://localhost:8080/login', {
			method: 'post',
			body: 'username=' + this.state.username + '&password=' + this.state.password,
			headers: { 'Content-type': 'application/x-www-form-urlencoded' }
		})
			.then((res) => {
				if (res.token) {
					console.log('I got a loginToken')
				}
				if (res.ok) {
					return res
				} else {
					alert("Invalid username and/or password")
					return res;
				}
			})
			.then(res => res.json())
			.then(json => {
				this.setState({
					token: json.token
				})
			})
	}

	callSignup = async (e) => {
		e.preventDefault()
		fetch('http://localhost:8080/signup', {
			method: 'post',
			body: 'username=' + this.state.username + '&password=' + this.state.password + '&email=' + this.state.email,
			headers: { 'Content-type': 'application/x-www-form-urlencoded' }
		})
		.then((res) => {
			if (res.ok) {
				alert("Account created with success !")
				return res
			} else {
				alert("Error: username already in use")
				return res
			}
		})
	}

	officeLogin = async () => {
		fetch('http://localhost:8080/auth/office?return=http://localhost:8081/subscribe/' + this.state.token)
        .then (res => {
            if (res.ok) {
                return res
            } else {
                let errorMessage = 'error', error = new Error(errorMessage)
                throw(error)
            }
        })
        .then(res => res.json())
        .then(json => {
            this.setState({
                officeUrl: json.signInUrl
            })
        })
    }

	handleChange(event) {
		this.setState({ username: event.target.value });
		console.log("username")
	}

	changePassword(event) {
		this.setState({ password: event.target.value });
		console.log("password")
	}

	changeEmail(event) {
		this.setState({ email: event.target.value });
		console.log("email")
	}

	render() {
		const { from } = '/'

		$(document).ready(function () {
			$('ul.tabs li').click(function () {
				var tab_id = $(this).attr('data-tab');

				$('ul.tabs li').removeClass('current');
				$('.tab-content').removeClass('current');

				$(this).addClass('current');
				$("#" + tab_id).addClass('current');
			})
		})

		return (
			<div>
				{
					<div id="container">
						<ul class="tabs">
							<li class="tab-link current" data-tab="tab-1">Login</li>
							<li class="tab-link" data-tab="tab-2">Register</li>
						</ul>

						<div id="tab-1" class="login tab-content current">
							<form onSubmit={this.callToken}>
								<div class="form-section">
									<span class="fa fa-user-o input-icon"></span>
									<input type="text" name="username" placeholder="Username" onChange={this.handleChange} required />
								</div>
								<div class="form-section">
									<span class="fa fa-unlock-alt input-icon"></span>
									<input type="password" name="password" placeholder="Password" onChange={this.changePassword} required />
								</div>
								<div class="form-section btn-container">
									<input type="submit" value="Login" />
								</div>
							</form>

							<br></br>

							<form onSubmit={this.officeLogin}>
								<div class="row">
									<div class="col-md-2">
										<img height="42" width="42" alt="" src="office_logo.png" />
									</div>
									<div class="col-md-10">
										<a href={ this.state.officeUrl } >Or login with Office 365</a>
									</div>
								</div>
							</form>
						</div>

						<div id="tab-2" class="register tab-content">
							<form onSubmit={this.callSignup}>
								<div class="form-section">
									<span class="fa fa-user-o input-icon"></span>
									<input type="text" name="username" placeholder="Username" onChange={this.handleChange} required />
								</div>
								<div class="form-section">
									<span class="fa fa-envelope-o input-icon"></span>
									<input name="email" placeholder="email address" type="email" onChange={this.changeEmail} required />
								</div>
								<div class="form-section">
									<span class="fa fa-unlock-alt input-icon"></span>
									<input type="password" name="password" placeholder="Password" onChange={this.changePassword} required />
								</div>
								<div class="form-section btn-container">
									<input type="submit" value="Register" />
								</div>
							</form>
						</div>
						{this.state.token && (
							<Redirect to={from || '/subscribe/' + this.state.token} />
						)}

					</div>

				}
			</div>
		)
	}
}
