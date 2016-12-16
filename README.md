# rmqo
Answering a small batch of Range Minimum Queries in practice

What is it?
-----------

Range Minimum Queries Offline (rmqo) is a powerful and flexible C++11
library implementing an algorithm for answering a batch of RMQs in practice. 
The theoretical time complexity of this algorithm is <b>n + O(q log q)</b> and the
extra space used is <b>O(q)</b>; where n is the size of the input array and q is the number
of queries. We write <b>n</b> to stress that the number of operations per entry of the 
input array should be a very small constant.

Why rmqo?
--------

Answering a small batch of RMQs is a core computational task in many real-world applications. 
With <i>small batch</i>, we mean that the number q of queries is o(n) and we have them all at hand. 
It is therefore not relevant to build an O(n)-sized data structure or spend O(n) time to build a more succinct one.  
It is well-known, among practitioners and elsewhere, that these data structures for on-line querying carry high constants in their pre-processing and querying time. We would thus like to answer this batch efficiently in practice. With <i>efficiently in practice</i>, we mean that we (ultimately) want to spend n + O(q) time and O(q) space. 

