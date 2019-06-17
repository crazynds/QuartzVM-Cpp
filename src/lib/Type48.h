/*
 * Type48.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef TYPE48_H_
#define TYPE48_H_

	#include <iostream>
	#include <bitset>

	class uint48{
    	private:
			uint32 eax;
			uint16 ax;
    	public:
    		uint48(){
    			eax=0;
    			ax=0;
    		}
    		uint48(const uint64 p){
				eax=p&0x0000FFFFFFFF;
				ax=p>>32;
    		}
    		uint64 inline toInt(){
    			return *((uint64*)this)&0x0000FFFFFFFFFFFF;
    			//return ((uint64)ax<<32)+eax;
    		}

    		void inline operator++(){
    			operator=(toInt()+1);
    		}
    		void inline operator = (uint64 x){
    			eax=x&0x0000FFFFFFFF;
    			ax=x>>32;
    		}
    		void operator += (uint48 x){
    			eax+=x.eax;
    			if(eax<x.eax)ax++;
    			ax+=x.ax;
    		}
    		void operator -= (uint48 x){
				if(eax<x.eax)ax--;
    			eax-=x.eax;
				ax-=x.ax;
			}
    		void operator *= (uint48 x){
    			register uint64 p=toInt();
				p*=x.toInt();
				operator =(p);
			}
    		void operator /= (uint48 x){
    			register uint64 p=toInt();
				p/=x.toInt();
				operator =(p);
			}
    		void operator %= (uint48 x){
    			register uint64 p=toInt();
				p%=x.toInt();
				operator =(p);
			}
    		void operator += (uint64 x){
    			register uint64 p=toInt();
				p+=x;
				operator =(p);
			}
			void operator -= (uint64 x){
				register uint64 p=toInt();
				p-=x;
				operator =(p);
			}
			void operator *= (uint64 x){
				register uint64 p=toInt();
				p*=x;
				operator =(p);
			}
			void operator /= (uint64 x){
				register uint64 p=toInt();
				p/=x;
				operator =(p);
			}
			void operator %= (uint64 x){
				register uint64 p=toInt();
				p%=x;
				operator =(p);
			}
			void operator >>= (uint64 x){
				register uint64 p=toInt();
				p>>=x;
				operator =(p);
			}
			void operator <<= (uint64 x){
				register uint64 p=toInt();
				p<<=x;
				operator =(p);
			}



    }__attribute__((packed));

    class int48{
        	private:
    			uint32 eax;
    			int16 ax;

        	public:
        		int48(){
        			eax=0;
        			ax=0;
        		}
        		int48(int64 p){
					eax=p&0x0000FFFFFFFF;
					ax=p>>32;
				}
        		int48(uint48 z){
        			uint64 p=z.toInt();
					eax=p&0x0000FFFFFFFF;
					ax=p>>32;
				}

        		int64 inline toInt(){
        			register int64 x=*(int64*)this;
        			x&=(int64)0x0000FFFFFFFFFFFF;
        			if(ax>=0)return x;
        			x|=(int64)0xFFFF000000000000;
        			return x;
        		}

        		void operator = (int64 x){
					eax=x&0x0000FFFFFFFF;
					ax=x>>32;
				}
				void operator += (int48 x){
					register int64 p=toInt();
					p+=x.toInt();
					operator =(p);
				}
				void operator -= (int48 x){
					register int64 p=toInt();
					p-=x.toInt();
					operator =(p);
				}
				void operator *= (int48 x){
					register int64 p=toInt();
					p*=x.toInt();
					operator =(p);
				}
				void operator /= (int48 x){
					register int64 p=toInt();
					p/=x.toInt();
					operator =(p);
				}
				void operator %= (int48 x){
					register int64 p=toInt();
					p%=x.toInt();
					operator =(p);
				}
				void operator += (int64 x){
					register int64 p=toInt();
					p+=x;
					operator =(p);
				}
				void operator -= (int64 x){
					register int64 p=toInt();
					p-=x;
					operator =(p);
				}
				void operator *= (int64 x){
					register int64 p=toInt();
					p*=x;
					operator =(p);
				}
				void operator /= (int64 x){
					register int64 p=toInt();
					p/=x;
					operator =(p);
				}
				void operator %= (int64 x){
					register int64 p=toInt();
					p%=x;
					operator =(p);
				}

        }__attribute__((packed));



#endif /* TYPE48_H_ */
