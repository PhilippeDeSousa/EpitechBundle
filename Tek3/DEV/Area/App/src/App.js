import React, { Component } from 'react';
import { BrowserRouter, Route } from 'react-router-dom';

import Index from './Views/Index';
import Services from './Views/Services';
import Subscribe from './Views/Subscribe';

class App extends Component {
    render() {
        return (
            <BrowserRouter>
                <div>
                    <Route exact={true} path='/' render={() => (
                        <div>
                            <Index />
                        </div>
                    )} />

                    <Route exact={false} path='/services' render={() => (
                        <div>
                            <Services />
                        </div>
                    )} />

                    <Route exact={false} path='/subscribe' render={() => (
                        <div>
                            <Subscribe />
                        </div>
                    )} />

                </div>
            </BrowserRouter>
        );
    }
}

export default App;
