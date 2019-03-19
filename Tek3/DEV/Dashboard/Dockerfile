# Base Images
FROM node

# Setting up the folders inside the docker
COPY ./Dashboard /Dashboard

# cd /Dashboard
WORKDIR /Dashboard

# Opening port 8080
EXPOSE 8080

# Updates the node_modules
RUN npm install

# Running the server
CMD ["node", "app.js"]