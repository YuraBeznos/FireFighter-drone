TARGETS=all build prepare check install clean uninstall format tests

.PHONY: docs

$(TARGETS):
	cd src && make $@

mosquitto: docker
	docker run --rm -ti ffd mosquitto -v -c /etc/mosquitto/conf.d/mosquitto.conf

docker:
	docker build ./ -t ffd

run: docker
	docker-compose up

docs:
	doxygen cfg/Doxyfile
	doxybook2 -c cfg/doxybook.json --input doxygen/xml/ --output docs
