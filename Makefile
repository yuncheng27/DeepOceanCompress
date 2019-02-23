#bin=FileCompress
bin=Test
cc=g++ -std=c++11

#$(bin):FileCompress.cpp
$(bin):Test.cpp
	$(cc) -o $@ $^

.PHONY:clean

clean:
	rm -f $(bin)
