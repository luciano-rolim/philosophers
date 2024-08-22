
	//Maybe Replace both usleep(300) by some proper thing, like a line 
// or shit like that, or maybe reduce time
// Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
// Test 1 800 200 200. The philosopher should not eat and should die.
// Test 5 800 200 200. No philosopher should die.
// Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
// Test 4 410 200 200. No philosopher should die.
// Test 4 310 200 100. One philosopher should die.
