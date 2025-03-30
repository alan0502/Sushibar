default: 
	cmake -S . -B build
	cd build && make 
	cd build/src && ./CG_2025_HW1
clean: 
	rm -r build