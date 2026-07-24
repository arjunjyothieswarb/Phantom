build-serv:
	cd server && \
	cmake -S . -B ./build/ && \
	cmake --build ./build/

clean-serv:
	rm -rf server/build/

clean-build-serv: clean-serv build-serv