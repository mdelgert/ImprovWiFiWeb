openssl req -x509 -newkey rsa:2048 -keyout cert.key -out cert.pem -days 365 -nodes -subj "/CN=demo2.local"
