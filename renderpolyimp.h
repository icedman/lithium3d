
{
	// find top and bottom
	pvertex_t vfirst=&polygon->vertices[0];
	pvertex_t vlast=&polygon->vertices[(polygon->numVertices)-1];
	pvertex_t vtop=vfirst;
	pvertex_t vbottom=vfirst;
	pvertex_t vtmp;
	
	int i;
	for (i=0;i<polygon->numVertices;i++) {
		vtmp=&polygon->vertices[i];
		if (vtop->screen.y > vtmp->screen.y) {
			vtop=vtmp;
		}
		if (vbottom->screen.y < vtmp->screen.y) {
			vbottom=vtmp;
		}
	}
		
	// scan edges
	edge_t leftedges[4];
	edge_t rightedges[4];
	pedge_t left;
	pedge_t right;
	
	// left
	left=&leftedges[0];
	vtmp=vtop;
	while(vtmp!=vbottom) {
		if (vtmp!=vfirst) {
			EdgeCalculate(left,vtmp,(vtmp-1));
			vtmp--;
		} else {
			EdgeCalculate(left,vtmp,vlast);
			vtmp=vlast;
		}
		left++;
	}
	// right
	right=&rightedges[0];
	vtmp=vtop;
	while(vtmp!=vbottom) {
		if (vtmp!=vlast) {
			EdgeCalculate(right,vtmp,(vtmp+1));
			vtmp++;
		} else {
			EdgeCalculate(right,vtmp,vfirst);
			vtmp=vfirst;
		}
		right++;
	}	

	// render scanlines
	left=&leftedges[0];
	right=&rightedges[0];

	if (left->length==0) left++;
	if (right->length==0) right++;
	
	s32 height,width;
	s32 x,y;
	s32 u,v;
	s32 uu,vv;
	s32 l,ll;
	s32 ww;

	u32 c;

	TRACE(left);

	ppixel_t pTarget;
	#undef GET_TEXEL
	#ifdef RENDER_8BIT
		u8* pSource;
		ppalette_t palette=texture->palette;
		int tmpindex;
		#define GET_TEXEL \
			tmpindex=pSource[((u>>FPP) + ((v>>FPP) << texture->shift))]; \
			pTexel=&palette->intensity[tmpindex][l>>FPP];
	#else
		ppixel_t pSource;
		#define GET_TEXEL \
			pTexel=pSource  + (u>>FPP) + ((v>>FPP) << texture->shift);
	#endif
	ppixel_t pTexel;

	u32 *pTarget32;
	u32 *pTarget32I;

	y=vtop->screen.y;
	height=vbottom->screen.y - vtop->screen.y;
	for(;height>0;height--) {

		// render scanline

		width=(right->x >>FPP) - (left->x >> FPP);
		x=left->x >> FPP;

		if (width<1 || x+width<0 || x>buffer->width || y>buffer->height || y<0 || y&1) {
			EdgeStep(left);
			if (left->length==0) left++;
			EdgeStep(right);
			if (right->length==0) right++;
			y++;
			continue;
		}

		u=left->u;
		v=left->v;
		l=left->l;

		ww=FPRECIP(width);
		uu=FPMUL((right->u - u),ww);
		vv=FPMUL((right->v - v),ww);
		ll=FPMUL((right->l - l),ww);

		// image space clipping
		if (width+x>=buffer->width) {
			width=(buffer->width-x)-1;
		}
		if (x<0) {
			x=abs(x);
			width-=x;
			u+=(uu*x); v+=(vv*x);
			x=0;
		}

		pTarget=(ppixel_t)(byte*)buffer->pixels  + ((x) + (y * buffer->pitch>>1));	
		#ifdef RENDER_8BIT
		pSource=(u8*)texture->pixels;
		#else
		pSource=(ppixel_t)texture->pixels;
		#endif

		pixel_t cc;
		pTexel=&cc;

		if ((u32)pTarget & 3) {
			GET_TEXEL;
			u+=uu; v+=vv;
			*pTarget++=*pTexel;
			width--;
		}

		pTarget32=(u32*)pTarget;
		pTarget32I=(pTarget32 + (buffer->pitch>>2));
		width=(width+2)>>1;
		x=0;

		uu<<=1;
		vv<<=1;
		ll<<=1;

		while(width--) {
			GET_TEXEL
			c=(*pTexel << 16) | *pTexel;
			pTarget32[x]=c;
			pTarget32I[x++]=c;
			u+=uu;v+=vv;l+=ll;
		}

		// next line

		EdgeStep(left);
		if (left->length==0) left++;

		EdgeStep(right);
		if (right->length==0) right++;

		y++;
	}
}

#undef RENDER_16BIT
#undef RENDER_8BIT
