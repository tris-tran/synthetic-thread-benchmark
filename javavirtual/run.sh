

javac -g:none Methods.java VirtualThreads.java 

# This suppose to enable all the memory at the start
# Could be intresting to allocate all the heap needed
#-XX:+AlwaysPreTouch

exec java -XX:+UnlockExperimentalVMOptions -XX:+UseEpsilonGC -Xms1G -Xmx1G -Xss1MB VirtualThreads $1
