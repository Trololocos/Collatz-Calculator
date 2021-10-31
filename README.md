
# Collatz Calculator
Program that calculates numbers of the Collatz Conjecture.

There are three algorithms used here:

 - The first one is simply implementing the basic algorithm. Nothing fancy here.
 - The second one just cuts off when our number is smaller than the one we started with. (It's a guarantee that all values that are smaller comply with the conjecture because we have calculated them)
 - The third one (*dynamic approach*) is a bit more nuanced.

### Dynamic approach
The basic idea is really simple: Store elements as we calculate them to avoid redundant calculations.
We could make a really big array but this is unpractical, how big do we make it? So I create memory as we need.
This would be fine, but once we surpass the index all previous memory becomes useless (same principle that allows for the second approach optimization). To avoid this, I implement a memory structure called ***mem_blocks***.

***mem_blocks*** is essentially a linked list of caches which has the functionality to "swap". Swapping is grabbing the first node and putting it in the back, empty. E.g `swap( {A->B->C} )` would return  `{B->C->0}`. It also allows for easy fetching and setting values in any index.


Unfortunately, all of the memory overhead of setting up memory is not worth it, performance wise, as is evident because doubling the size of the caches also doubles the runtime performance, so the naïve approaches work significantly better, which is really disappointing after all of the effort to put it all together. I had fun, though, so it wasn't entirely useless.
