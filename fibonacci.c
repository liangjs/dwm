void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh, bw;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;

	bw = n == 1 ? 0 : borderpx;
	
	nx = mon->wx + mon->gappx;
	ny = mon->gappx;
	nw = mon->ww - mon->gappx;
	nh = mon->wh - mon->gappx;
	
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
					nw = mon->ww * mon->mfact - mon->gappx;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw - mon->gappx;
			i++;
		}
		resize(c, nx, ny + mon->gappx, nw - 2 * bw - mon->gappx, nh - 2 * bw - mon->gappx, bw, 0);
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
