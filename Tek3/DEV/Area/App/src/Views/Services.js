import React, { Component } from 'react'
import 'bootstrap/dist/css/bootstrap.css'
//import '../Public/Index.css'

export default class Services extends Component {

    state = {
        post: '',
        resToPost: '',
        officeUrl: '',
        googleUrl: '',
		token: window.location.href.split('/')[4]
    }

    componentDidMount() {
        this.callApi()
        this.callGoogle()
    }

    callApi = async () => {

        fetch('http://localhost:8080/auth/office?return=http://localhost:3000/office/success&token=' + this.state.token)
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

    callGoogle = async () => {

        fetch('http://localhost:8080/auth/google?return=http://localhost:3000/google/success&token=' + this.state.token)
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
                googleUrl: json.authUrl
            })
        })

    }

    render () {

        return (
            <div>
                <h1>Services page</h1>
				<h3>Your token is {this.state.token}</h3>
                <p>You can login to office by pressing:</p>
                <a href={ this.state.officeUrl }> Click me! </a>

                <p>You can also login to google by pressing:</p>
                <a href={ this.state.googleUrl }> Click me too! </a>
            </div>

        )
    }
}
