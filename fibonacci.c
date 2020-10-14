void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh, bw;
	unsigned int gap;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next))
		if (ISVISIBLE(c))
			++n;
	if(n == 0)
		return;

	bw = n == 1 ? 0 : borderpx;
	gap = n == 1 ? 0 : mon->gappx;
	
	nx = mon->wx + gap;
	ny = gap;
	nw = mon->ww - gap;
	nh = mon->wh - gap;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact - gap;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw - gap;
			i++;
		}
		resize(c, nx, ny + gap, nw - 2 * bw - gap, nh - 2 * bw - gap, bw, 0);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
