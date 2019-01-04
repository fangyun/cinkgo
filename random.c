static __thread unsigned long pmseed = 29264;

void fast_srandom(unsigned long seed_) {
	pmseed = seed_;
}
