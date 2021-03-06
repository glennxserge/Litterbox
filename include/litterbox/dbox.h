#ifndef DBOX_H
#define DBOX_H

const u16 dbox_palette[6] = {
	RGB15(31, 31, 31),
	RGB15(0, 0, 0),
	RGB15(26, 26, 11),
	RGB15(15, 24, 28),
	RGB15(29, 30, 23),
	RGB15(21, 22, 5)
};

const u8 dbox[9][64] = {
  {
	0,  0,  0,  71, 71, 71, 71, 71, 
	0,  0,  71, 74, 74, 74, 74, 74, 
	0,  71, 72, 72, 72, 72, 72, 72, 
	71, 72, 72, 72, 73, 73, 73, 73, 
	71, 72, 72, 73, 73, 0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0
  },
  {
	71, 71, 71, 71, 71, 71, 71, 71, 
	74, 74, 74, 74, 74, 74, 74, 74, 
	72, 72, 72, 72, 72, 72, 72, 72, 
	73, 73, 73, 73, 73, 73, 73, 73, 
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0
  },
  {
	71, 71, 71, 71, 71, 0,  0,  0,  
	74, 74, 74, 74, 74, 71, 0,  0,  
	72, 72, 72, 72, 72, 72, 71, 0,  
	73, 73, 73, 73, 72, 72, 72, 71, 
	0,  0,  0,  73, 73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71
  },
  {
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0
  },
  {
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0
  },
  {
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71
  },
  {
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 0,  0,  0,  0,  
	71, 72, 72, 73, 73, 0,  0,  0,  
	71, 72, 72, 72, 73, 73, 73, 73, 
	0,  71, 72, 72, 72, 72, 72, 72, 
	0,  0,  71, 75, 75, 75, 75, 75, 
	0,  0,  0,  71, 71, 71, 71, 71
  },
  {
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	0,  0,  0,  0,  0,  0,  0,  0,  
	73, 73, 73, 73, 73, 73, 73, 73, 
	72, 72, 72, 72, 72, 72, 72, 72, 
	75, 75, 75, 75, 75, 75, 75, 75, 
	71, 71, 71, 71, 71, 71, 71, 71
  },
  {
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  0,  73, 72, 72, 71, 
	0,  0,  0,  73, 73, 72, 72, 71, 
	73, 73, 73, 73, 72, 72, 72, 71, 
	72, 72, 72, 72, 72, 72, 71, 0,  
	75, 75, 75, 75, 75, 71, 0,  0,  
	71, 71, 71, 71, 71, 0,  0,  0
  }
};

#endif //DBOX_H