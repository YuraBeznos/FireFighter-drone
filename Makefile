TARGETS=all build prepare check install clean uninstall format tests

$(TARGETS):
	cd src && make $@

mosquitto: docker
	docker run --rm -ti ffd mosquitto -v -c /etc/mosquitto/conf.d/mosquitto.conf

docker:
	docker build ./ -t ffd

run: docker
	docker-compose up
