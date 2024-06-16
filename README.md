# Nuance Vector DB

Nuance is a Vector Database that stores and serves word embeddings

docker build -t tcp_server .

docker run -d -p 8080:8080 tcp_server

echo "Hello, Server" | nc localhost 8081