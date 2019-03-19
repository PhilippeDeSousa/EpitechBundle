const moment = require('moment')

module.exports = {
    CreateJson: function (req, res) {
        const json = {}
        json.client = {}
        json.client.host = req.connection.remoteAddress

        json.server = {}
        json.server.current_time = moment().unix()

        const service1 = {}
        service1.name = "weather"
        service1.actions = {}
        service1.actions.name = "check_rain"
        service1.actions.description = "Check if it's raining in the city"

        service1.reactions = {}
        service1.reactions.name = "send_email"
        service1.reactions.description = "Send an email to the user"

        const service2 = {}
        service2.name = "timer"
        service2.actions = {}
        service2.actions.name = "alarm"
        service2.actions.description = "Check is the time is over"

        service2.reactions = []
		service2.reactions[0] = {}
        service2.reactions[0].name = "pop_alert"
        service2.reactions[0].description = "Alert the user"
		service2.reactions[1] = {}
		service2.reactions[1].name = "pop_notif"
        service2.reactions[1].description = "Send a notification to the user"

		const service3 = {}
        service3.name = "trends"
        service3.actions = {}
        service3.actions.name = "news"
        service3.actions.description = "Get the news about a subject"

        service3.reactions = {}
        service3.reactions.name = "send_email"
        service3.reactions.description = "Send an email to the user"

        json.server.services = [service1, service2, service3]

        return json;
    }
}
