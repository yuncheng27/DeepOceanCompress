#bin=FileCompress
bin=Test
cc=g++

#$(bin):FileCompress.cpp
$(bin):Test.cpp
	$(cc) -o $@ $^

.PHONY:clean

clean:
	rm -f $(bin)
