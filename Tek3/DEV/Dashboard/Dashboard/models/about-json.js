const widgetSchema = ({
    name: { type: String },
    description: { type: String },
    params: [{
        name: { type: String },
        type: { type: String }
    }]
})

const serviceSchema = ({
    name: { type: String },
    widgets: [ widgetSchema ]
})

const aboutSchema = ({
    client: ({
        host: {
            type: Number
        }
    }),
    server: ({
        current_time: {
            type: String
        },
        services: [ serviceSchema ]
    })
  })
  
  module.exports = { aboutSchema, serviceSchema, widgetSchema } ;