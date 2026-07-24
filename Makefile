build-all: build-serv build-cli

build-serv:
	cd server && \
	cmake -S . -B ./build/ && \
	cmake --build ./build/

build-cli:
	cd client && \
	cmake -S . -B ./build/ && \
	cmake --build ./build/


clean-cli:
	rm -rf client/build/

clean-serv:
	rm -rf server/build/

clean-all: clean-cli clean-serv


clean-build-serv: clean-serv build-serv

clean-build-cli: clean-cli build-cli

clean-rebuild: clean-build-serv clean-build-cli