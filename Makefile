TARGETS=all build prepare check install clean uninstall format unittests e2e-test-a e2e-test-b policy-tests

.PHONY: docs e2e-clean docker-compose-stop
.NOTPARALLEL: e2e-tests

$(TARGETS):
	cd src && make $@

mosquitto: docker
	docker run --rm -ti ffd mosquitto -v -c /etc/mosquitto/conf.d/mosquitto.conf

docker:
	docker build ./ -t ffd

docker-clean:
	docker ps -a -q |xargs docker rm

run: docker
	docker-compose up

docs:
	doxygen cfg/Doxyfile
	doxybook2 -c cfg/doxybook.json --input doxygen/xml/ --output docs

docker-compose-stop:
	docker-compose stop

docker-compose-up: docker docker-compose-stop
	docker-compose up -d

e2e-prepare: docker-compose-up

e2e-tests: e2e-prepare e2e-test-a e2e-test-b
	docker-compose stop

tests: e2e-tests
