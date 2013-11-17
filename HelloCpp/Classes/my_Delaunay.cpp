#include "my_Delaunay.h"
float pow2(float x){
    return x*x;
}
void init4(float vec[4],float x,float y,float z,float w){
    vec[0]=x;
    vec[1]=y;
    vec[2]=z;
    vec[3]=w;
}
void veccopy(float src[4],float dest[4]){
    dest[0]=src[0];
    dest[1]=src[1];
    dest[2]=src[2];
    dest[3]=src[3];
    
}
double calCircle(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3,
                        float &x,float &y)
// ‰»Î»˝µ„(_x1,_y1),(_x2,y2),(_x3,_y3)£¨µ√µΩ‘≤–ƒ◊¯±Í(x,y)£¨«∞∂À∑µªÿ∞Îæ∂µƒ∆Ω∑Ω
{
	double r2;//Õ‚Ω”‘≤∞Îæ∂µƒ∆Ω∑Ω
    
	//«ÛÀÆ∆Ωµƒ±ﬂ
	int EvenEdgeIndex=0;//º«¬ºµ⁄º∏∏ˆ±ﬂÀÆ∆Ω
	int count=0;
	if(fabs(_y1-_y2)<0.01){//ÀÆ∆Ω
		EvenEdgeIndex=1;
		count++;
	}
	if(fabs(_y2-_y3)<0.01){
		EvenEdgeIndex=2;
		count++;
	}
	if(fabs(_y1-_y3)<0.01){
		EvenEdgeIndex=3;
		count++;
	}
	if(count>1){
        //		cout<<"error circle"<<endl;
		return -inf;
        
	}
    
	float x1,y1,x2,y2,x3,y3;
	switch(EvenEdgeIndex){
        case 1://»Áπ˚(_x1,_y1)-(_x2,_y2)ÀÆ∆Ω
            x1=_x2;
            y1=_y2;
            x2=_x3;
            y2=_y3;
            x3=_x1;
            y3=_y1;
            break;
        case 2://»Áπ˚(_x2,_y2)-(_x3,_y3)ÀÆ∆Ω
            x1=_x3;
            y1=_y3;
            x2=_x1;
            y2=_y1;
            x3=_x2;
            y3=_y2;
            break;
        case 3://»Áπ˚(_x3,_y3)-(_x1,_y1)ÀÆ∆Ω
            x1=_x1;
            y1=_y1;
            x2=_x2;
            y2=_y2;
            x3=_x3;
            y3=_y3;
            break;
        case 0:
            x1=_x1;
            y1=_y1;
            x2=_x2;
            y2=_y2;
            x3=_x3;
            y3=_y3;
            break;
            
	}
    
	//«Û(x1,y1)-(x2,y2)µƒ¥πœﬂ–±¬
	float k1;
    
	k1=-(x2-x1)/(y2-y1);//”…”⁄(x1,y1)-(x2,y2)≤ªÀÆ∆Ω£¨À˘“‘y2±ÿ≤ªµ»”⁄y1
	//«Û(x2,y2)-(x3,y3)µƒ¥πœﬂ–±¬
	float k2;
	k2=-(x3-x2)/(y3-y2);//”…”⁄(x2,y2)-(x3,y3)≤ªÀÆ∆Ω£¨À˘“‘y3±ÿ≤ªµ»”⁄y2
	//«Û(x1,y1)-(x2,y2)÷–µ„(a,b)
	float a,b;
	a=(x1+x2)/2;
	b=(y1+y2)/2;
	//«Û(x2,y2)-(x3,y3)÷–µ„(c,d)
	float c,d;
	c=(x2+x3)/2;
	d=(y2+y3)/2;
	//«Û¡ΩÃı÷–¥πœﬂµƒΩªµ„£®¡ΩÃı÷–¥πœﬂµƒ∑Ω≥Ã «£∫y-b=k1x-ak1 ∫Õ y-d=k2x-ck2£©
	x=(a*k1-c*k2+d-b)/(k1-k2);
	y=k1*x-a*k1+b;
	//«Û∞Îæ∂µƒ∆Ω∑Ω
	r2=pow2(x-x1)+pow2(y-y1);
	return r2;
    
}





int getIndexOfp_IDtri1ToIDtri2(CIDTriangle*pIDtri1,CIDTriangle*pIDtri2)
//«Û*pIDtri1µƒµ⁄º∏∏ˆ÷∏’Î÷∏œÚ*pIDtri2
//»Áπ˚*pIDtri1√ª”–÷∏œÚ*pIDtri2µƒ÷∏’Î£¨‘Ú∑µªÿ-1
{
    int index=0;
	for(int i=0;i<=2;i++){
		if(pIDtri1->p[i]==pIDtri2){
            index=i;
			break;
		}
	}
	if(index<=2){// «break≥ˆ¿¥µƒ£¨Àµ√˜*pIDtri1”–÷∏’Î÷∏œÚ*pIDtri2£¨pIDtri1->p[i]º¥Œ™¥À÷∏’Î
		return index;
	}else{
		cout<<"error getIndexOfp_IDtri1ToIDtri2"<<endl;
		return -1;
	}
}
int getIndexOfVert_inIDtri1notinIDtri2(CIDTriangle*pIDtri1,CIDTriangle*pIDtri2)
//«Û*pIDtri1÷–µ⁄º∏∏ˆ∂•µ„≤ª‘⁄*pIDtri2÷–£¨∑µªÿ’“µΩµƒµ⁄“ª∏ˆ∑˚∫œ¥ÀÃıº˛µƒ∂•µ„∫≈
{
    //	int I[3];
    //	int p=0;
	for(int i=0;i<=2;i++){
		int ID=pIDtri1->vID[i];
		//ø¥ID «∑Ò‘⁄*pIDtri2÷–
		bool isin=false;
		for(int j=0;j<=2;j++){
			int _ID=pIDtri2->vID[j];
			if(ID==_ID){
				isin=true;
				break;
			}
		}//µ√µΩisin
		if(!isin){
            //			I[p++]=i;
			return i;
		}
	}
	//√ª’“µΩ
	return -1;
    //	if(p==1){
    //		return I[0];
    //	}else if(p==0){
    //		cout<<"errror"<<endl;
    //		return -1;
    //	}else{
    //		cout<<"error"<<endl;
    //		exit(0);
    //	}
    
}

int pointInIDtri(float v[4],CIDTriangle*pIDtri,myvector<Cv4>&vlist,int&edgeID)
//≈–∂œID∫≈∂•µ„ «∑Ò‘⁄*pIDtriƒ⁄ªÚ±ﬂΩÁ…œ
// ‰»Îµƒvµƒv[Y]±ÿ–Î «0
//∑µªÿ÷µ0,1,2,3∑÷±¥˙±Ì£∫‘⁄Õ‚£¨‘⁄ƒ⁄£¨‘⁄±ﬂ…œ£¨‘⁄∂•µ„…œ
{
	float x=v[X];
	float y=v[Z];
	float x1=vlist[pIDtri->vID[0]].v[X];
	float y1=vlist[pIDtri->vID[0]].v[Z];
	float x2=vlist[pIDtri->vID[1]].v[X];
	float y2=vlist[pIDtri->vID[1]].v[Z];
	float x3=vlist[pIDtri->vID[2]].v[X];
	float y3=vlist[pIDtri->vID[2]].v[Z];
	int onEdgeCount=0;
	//ø¥(x,y) «∑Ò‘⁄(x1,y1)-(x2,y2)◊Û≤‡
	{
		//«Û(x1,y1)-(x2,y2)µƒ”“∑®œÚ¡ø
		float nx=y1-y2;//◊¢“‚£¨‘⁄œ¬√Ê◊¯±Íœµœ¬£¨œÚ¡ø(x,y)µƒ”“∑®œÚ¡ø «(-y,x)
        //        |---> x
        //        |
        //       \|/
        //        z
        //∂¯‘⁄œ¬√Ê◊¯±Íœµœ¬£¨œÚ¡ø(x,y)µƒ”“∑®œÚ¡ø «(y,-x)
        //        z
        //       /|\
        //        |
        //        |
        //        -----> x
		float ny=x2-x1;
		//«Û”Î(x,y)-(x1,y1)Õ¨œÚµƒœÚ¡ø
		float vecx=x1-x;
		float vecy=y1-y;
		//ø¥”Î(nx,ny)”Î(vecx,vecy)µƒµ„ª˝ «∑ÒŒ™’˝
		float dot=nx*vecx+ny*vecy;
		if(dot<0)return 0;//≤ª‘⁄ƒ⁄
		else if(dot==0){//‘⁄±ﬂ…œ
			edgeID=0;
			onEdgeCount++;
		}
	}
	//ø¥(x,y) «∑Ò‘⁄(x2,y2)-(x3,y3)◊Û≤‡
	{
		//«Û(x2,y2)-(x3,y3)µƒ”“∑®œÚ¡ø
		float nx=y2-y3;
		float ny=x3-x2;
		//«Û”Î(x,y)-(x2,y2)Õ¨œÚµƒœÚ¡ø
		float vecx=x2-x;
		float vecy=y2-y;
		//ø¥”Î(nx,ny)”Î(vecx,vecy)µƒµ„ª˝ «∑ÒŒ™’˝
		float dot=nx*vecx+ny*vecy;
		if(dot<0)return 0;//≤ª‘⁄ƒ⁄
		else if(dot==0){//‘⁄±ﬂ…œ
			edgeID=1;
			onEdgeCount++;
		}
	}
	//ø¥(x,y) «∑Ò‘⁄(x3,y3)-(x1,y1)◊Û≤‡
	{
		//«Û(x3,y3)-(x1,y1)µƒ”“∑®œÚ¡ø
		float nx=y3-y1;
		float ny=x1-x3;
		//«Û”Î(x,y)-(x3,y3)Õ¨œÚµƒœÚ¡ø
		float vecx=x3-x;
		float vecy=y3-y;
		//ø¥”Î(nx,ny)”Î(vecx,vecy)µƒµ„ª˝ «∑ÒŒ™’˝
		float dot=nx*vecx+ny*vecy;
		if(dot<0)return 0;//≤ª‘⁄ƒ⁄
		else if(dot==0){//‘⁄±ﬂ…œ
			edgeID=2;
			onEdgeCount++;
		}
	}
	//≤ª‘⁄Õ‚
	if(onEdgeCount==0){
		return 1;//‘⁄ƒ⁄
	}else if(onEdgeCount==1){
		return 2;//‘⁄±ﬂ…œ
	}else{
		return 3;//‘⁄∂•µ„…œ
	}
    
}
void flip(CIDTriangle*pAdjIDtri,CIDTriangle*pnewIDtri,const int ID,float v[4],myvector<Cv4>&vlist,myvector<CIDTriangle*>&pIDtriList,int&count){
	if(count>20){
		return;
	}
	//ø¥pAdjIDtriµƒÕ‚Ω”‘≤ «∑Ò∞¸∫¨∂•µ„ID£®“‡º¥v£©
	if(!pAdjIDtri->circleAlreadyGet){//»Áπ˚Õ‚Ω”‘≤ªπ√ª”–«Û≥ˆπ˝£¨«ÛÕ‚Ω”‘≤≤¢±£¥Ê
		//«ÛpAdjIDtriµƒÕ‚Ω”‘≤
		float x1,z1,x2,z2,x3,z3;//pAdjIDtri»˝∏ˆ∂•µ„µƒ(x,z)◊¯±Í
		x1=vlist[pAdjIDtri->vID[0]].v[X];
		z1=vlist[pAdjIDtri->vID[0]].v[Z];
		x2=vlist[pAdjIDtri->vID[1]].v[X];
		z2=vlist[pAdjIDtri->vID[1]].v[Z];
		x3=vlist[pAdjIDtri->vID[2]].v[X];
		z3=vlist[pAdjIDtri->vID[2]].v[Z];
		pAdjIDtri->r2=calCircle(x1,z1,x2,z2,x3,z3,pAdjIDtri->x,pAdjIDtri->z);
		pAdjIDtri->circleAlreadyGet=true;
		
	}
	//ø¥ID£®“‡º¥v£© «∑Ò‘⁄pAdjIDtriµƒÕ‚Ω”‘≤ƒ⁄
	if(pAdjIDtri->r2<0)return;
	if(isnan(pAdjIDtri->r2))return;
	//ø¥pAdjIDtriµƒÕ‚Ω”‘≤ «∑Ò∞¸∫¨v
	//«ÛvµΩ‘≤–ƒ(x,z)µƒæ‡¿Î∆Ω∑Ω
	double d2=pow2(v[X]-pAdjIDtri->x)+pow2(v[Z]-pAdjIDtri->z);
	if(d2<0)return;
	if(isnan(d2))return;
	if(d2>=pAdjIDtri->r2)return;//ID≤ª‘⁄pAdjIDtriµƒÕ‚Ω”‘≤ƒ⁄
    
    
    
	//»Áπ˚ID‘⁄pAdjIDtriµƒÕ‚Ω”‘≤ƒ⁄
	//Ω¯––∂‘Ω«œﬂ∏¸ªª
	//                  ID0                                   ID0
	//thirdID ----------/|                  thirdID-----------|
	//         \       / |                          \ - _1_   |
	//          \     / ID                ==>        \      -ID
	//           \   / /                              \  2  /
	//            \ //                                 \  /
	//            ID1                                  ID1
	int ID0=pnewIDtri->vID[1];
	int ID1=pnewIDtri->vID[2];
	//–Ë“™∏¸ªªpAdjIDtri”ÎpnewIDtriππ≥…µƒÀƒ±ﬂ–Œµƒ∂‘Ω«œﬂ
	//«ÛpAdjIDtri≤ª”ÎpIDtriπ´”√µƒ∂•µ„ID
	int thirdindex=getIndexOfVert_inIDtri1notinIDtri2(pAdjIDtri,pnewIDtri);
	int thirdID=pAdjIDtri->vID[thirdindex];
	if(thirdindex==-1){
		cout<<"error thirdindex==-1"<<endl;
		return;
	}
	//”√–¬µƒ»˝Ω«–ŒpIDtri1,pIDtri2»°¥˙pnewIDtri∫ÕpAdjIDtri
	CIDTriangle*pIDtri1,*pIDtri2;
	pIDtri1=new CIDTriangle();
	pIDtri2=new CIDTriangle();
	//…Ë∂•µ„£®æ˘“‘IDŒ™∆µ„£©
	pIDtri1->setvID(ID,ID0,thirdID);
	pIDtri2->setvID(ID,thirdID,ID1);
	//…Ë÷∏’Î
	pIDtri1->setp(pnewIDtri->p[0],pAdjIDtri->p[(thirdindex+2)%3],pIDtri2);
	pIDtri2->setp(pIDtri1,pAdjIDtri->p[thirdindex],pnewIDtri->p[2]);
    
	//Õ‚Œß»˝Ω«–Œµƒ÷∏’Î–ﬁ’˝
	//Õ®π˝ID0thirdIDœ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
	{
		CIDTriangle*_pAdjIDtri=pAdjIDtri->p[(thirdindex+2)%3];
		if(_pAdjIDtri!=NULL){
			//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpAdjIDtri
			int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pAdjIDtri);
			if(index==-1)return;
			//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpIDtri1
			_pAdjIDtri->p[index]=pIDtri1;
		}
		
	}
	//Õ®π˝thirdIDID1œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
	{
		CIDTriangle*_pAdjIDtri=pAdjIDtri->p[thirdindex];
		if(_pAdjIDtri!=NULL){
			//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpAdjIDtri
			int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pAdjIDtri);
			if(index==-1)return;
			//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpIDtri2
			_pAdjIDtri->p[index]=pIDtri2;
		}
		
	}
	//Õ®π˝IDID0œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
	{
		CIDTriangle*_pAdjIDtri=pnewIDtri->p[0];
		if(_pAdjIDtri!=NULL){
			//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpnewIDtri
			int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pnewIDtri);
			if(index==-1)return;
			//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpIDtri1
			_pAdjIDtri->p[index]=pIDtri1;
		}
		
	}
	//Õ®π˝IDID1œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
	{
		CIDTriangle*_pAdjIDtri=pnewIDtri->p[2];
		if(_pAdjIDtri!=NULL){
			//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpnewIDtri
			int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pnewIDtri);
			if(index==-1)return;
			//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpIDtri2
			_pAdjIDtri->p[index]=pIDtri2;
		}
	}
	//”√pIDtri1∫ÕpIDtri2ÃÊªªpnewIDtri∫ÕpAdjIDtri
	//Ω´pIDtri1º”»ÎpIDtriList
	pIDtriList.push_back(pIDtri1);
	//Ω´pIDtri2º”»ÎpIDtriList
	pIDtriList.push_back(pIDtri2);
    
	//Ω´pnewIDtri±Íº«Œ™removed
	pnewIDtri->removed=true;
	//Ω´pIDtri1,pIDtri2º”◊˜pnewIDtriµƒ∫¢◊”
	pnewIDtri->q.push_back(pIDtri1);
	pnewIDtri->q.push_back(pIDtri2);
    
	//Ω´pAdjIDtri±Íº«Œ™removed
	pAdjIDtri->removed=true;
	pAdjIDtri->q.push_back(pIDtri1);
	pAdjIDtri->q.push_back(pIDtri2);
    
    
	//µ›πÈ
    
	if(pIDtri1->p[1]!=NULL){
		count++;
		flip(pIDtri1->p[1],pIDtri1,ID,v,vlist,pIDtriList,count);
		count--;
	}
    
	
    
	if(pIDtri2->p[1]!=NULL){
		count++;
		flip(pIDtri2->p[1],pIDtri2,ID,v,vlist,pIDtriList,count);
		count--;
	}
    
	
    
}

void locIDPoint(float v[4],CIDTriangle*pIDtri,myvector<Cv4>&vlist,CIDTriangle*&pTagIDtri,int&judge,int&edgeID)
//µΩ»˝Ω« ˜÷–»•≤È’“IDµ„Œª”⁄ƒƒ∏ˆ»˝Ω«–Œ£¨∑µªÿ÷∏œÚ¥À»˝Ω«–Œµƒ÷∏’ÎpTagIDtri
//pTagIDtri◊Ó≥ı¥´»Î±ÿ–ÎŒ™NULL£¨∑Ò‘Ú≤ªƒ‹π§◊˜
//judge==1±Ì æ‘⁄ƒ⁄≤ø£¨judge==2±Ì æ‘⁄±ﬂ…œ£¨judge==3±Ì æ‘⁄∂•µ„…œ
//◊¢“‚£¨Œ™¡À”≈ªØ£¨’‚¿Ô∂‘”⁄¬‰‘⁄∂•µ„…œµƒ«Èøˆ£¨≤ª∑µªÿ’˝»∑µƒpIDtri
{
	//ø¥IDµ„ «∑ÒŒª”⁄pIDtri÷–
	judge=pointInIDtri(v,pIDtri,vlist,edgeID);
	if(judge==1||judge==2){//»Áπ˚Œª”⁄ƒ⁄≤øªÚ±ﬂœﬂ…œ
		int nchildIDtri=(int)pIDtri->q.size();
		if(nchildIDtri==0){
			pTagIDtri=pIDtri;
			return;
		}else{
			//µ›πÈ◊”Ω⁄µ„
			for(int i=0;i<nchildIDtri;i++){
				locIDPoint(v,pIDtri->q[i],vlist,pTagIDtri,judge,edgeID);
				if(pTagIDtri!=NULL||judge==3)return;
			}
		}
	}else{
		return;
	}
    
}
void Delaunay(myvector<Cv4>&vlist,
			  float xmin,float xmax,float zmin,float zmax,
			  myvector<CIDTriangle*>&pIDtriList)
//Delaunay»˝Ω«∆ ∑÷
// ‰»Îµ„‘∆mesh.vlist£¨∫Õµ„‘∆(x,z)∑∂Œß£¨ÃÓ≥‰mesh.IDtriList
{
	//ππ‘Ï≥¨º∂»˝Ω«–Œ
	//   a/2   a  a/2
	// v1_____________v3
	//   \ |   |   | /
 	//    \| b |   |/
	//     \---|---/
	//      \ b|  /
	//       \ | /
	//        \|/
	//         v2
	//   ∆‰÷–a=xmax-xmin£¨b=zmax-zmin
	//
	//º∆À„≥¨º∂»˝Ω«–Œµƒ»˝∏ˆ∂•µ„
	float margin=10000;//margin»°µ√◊„πª¥Û£¨“‘±£÷§Ω´¿¥…æ≥˝π˝∫¨π˝≥§±ﬂµƒ»˝Ω«–Œ ±ƒ‹Ω´≥¨º∂»˝Ω«–Œ…æ≥˝
	float a=xmax-xmin;
	float b=zmax-zmin;
	float v1[4],v2[4],v3[4];
	init4(v1,xmin-a/2-margin,0,zmin-margin,1);
	init4(v2,(xmin+xmax)/2,0,zmin+b+b+margin,1);
	init4(v3,xmax+a/2+margin,0,zmin-margin,1);
	//Ω´≥¨º∂»˝Ω«–Œµƒ»˝∏ˆ∂•µ„v1,v2,v3º”»ÎµΩ∂•µ„¡–±Ì
	vlist.grow();
	int ID0=(int)vlist.size()-1;
	veccopy(v1,vlist[ID0].v);
    
	vlist.grow();
	int ID1=ID0+1;
	veccopy(v2,vlist[ID1].v);
    
	vlist.grow();
	int ID2=ID1+1;
	veccopy(v3,vlist[ID2].v);
    
	//…˙≥…≥¨º∂»˝Ω«–Œ
	CIDTriangle*pIDtri=new CIDTriangle();
	pIDtri->setvID(ID0,ID1,ID2);
	pIDtri->setp(NULL,NULL,NULL);
    
	//Ω´pIDtriº”»ÎpIDtriList
	pIDtriList.push_back(pIDtri);
    
    
    
    
    
	//--------------------ø™ º÷µ„≤Â»Î
	int _nv=(int)vlist.size()-3;//◊Ó∫Û»˝∏ˆ∂•µ„≤ª‘Ÿ≤Â»Î
	for(int ii=0;ii<_nv;ii++){
		const int ID=ii;//∂•µ„À˜“˝∫≈
		float v[4];
		veccopy(vlist[ID].v,v);//◊¯±Í
		v[Y]=0;
		//≤Â»ÎID∫≈∂•µ„
		//ø¥ID∂•µ„Œª”⁄ƒƒ∏ˆ»˝Ω«–Œ
		CIDTriangle*pIDtri=NULL;//pIDtri∞¸∫¨ID∂•µ„
		int judge=0;
		int edgeID=-1;
		locIDPoint(v,pIDtriList[0],vlist,pIDtri,judge,edgeID);
		if(pIDtri==NULL){
			continue;
		}
        
		if(judge==2){//»Áπ˚¬‰‘⁄»˝Ω«–Œ±ﬂ…œ
			//         ID0
			//       ID/ \
			// edgeID *   \
			//       /     \
			//      /_______\
			//    ID1       ID2
			int ID0=pIDtri->vID[edgeID];
			int ID1=pIDtri->vID[(edgeID+1)%3];
			int ID2=pIDtri->vID[(edgeID+2)%3];
			//ø¥±ﬂedgeIDµƒ¡⁄æ”÷∏’Î «∑ÒŒ™ø’
			if(pIDtri->p[edgeID]==NULL){//»Áπ˚edgeIDµƒ¡⁄æ”÷∏’ÎŒ™ø’
				//         ID0
				//       ID/ \
				// edgeID /\ 0\
				//       /   \ \
				//      /__1___\\
				//    ID1       ID2
				//pIDtri∑÷¡—Œ™¡Ω∏ˆ»˝Ω«–Œ
				//…˙≥…–¬»˝Ω«–Œ
				myvector<CIDTriangle*> pnewIDtri;
				pnewIDtri.resize(2);
				pnewIDtri[0]=new CIDTriangle();
				pnewIDtri[1]=new CIDTriangle();
				//Œ™–¬»˝Ω«–Œ…Ë∂®∂•µ„(æ˘“‘÷––ƒµ„ID◊˜Œ™∆ ºµ„)
				pnewIDtri[0]->setvID(ID,ID2,ID0);
				pnewIDtri[1]->setvID(ID,ID1,ID2);
				//…Ë∂®–¬‘ˆ»˝Ω«–Œµƒ¡⁄Ω”÷∏’Î
				pnewIDtri[0]->setp(pnewIDtri[1],pIDtri->p[(edgeID+2)%3],NULL);
				pnewIDtri[1]->setp(NULL,pIDtri->p[(edgeID+1)%3],pnewIDtri[0]);
				//∏¸–¬pIDtri¡⁄Ω”»˝Ω«–Œµƒ÷∏’Î
				//Õ®π˝ID2ID0œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pIDtri->p[(edgeID+2)%3];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pIDtri);
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[0]
						if(index==-1)continue;
						_pAdjIDtri->p[index]=pnewIDtri[0];
					}
                    
				}
				//Õ®π˝ID1ID2œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pIDtri->p[(edgeID+1)%3];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pIDtri);
						if(index==-1)continue;
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[0]
						_pAdjIDtri->p[index]=pnewIDtri[1];
					}
                    
				}
				//Ω´–¬‘ˆ»˝Ω«–Œº”»ÎpIDtriList
				pIDtriList.push_back(pnewIDtri[0]);
				pIDtriList.push_back(pnewIDtri[1]);
				
				//Ω´pIDtri±Íº«Œ™removed
				pIDtri->removed=true;
				//Ω´pnewIDtri[0]~pnewIDtri[1]º”◊˜pIDtriµƒ∫¢◊”
				pIDtri->q.push_back(pnewIDtri[0]);
				pIDtri->q.push_back(pnewIDtri[1]);
                int count=0;
				//“¿¥ŒºÏ≤È∏˜pnewIDtriµƒp[1]µƒ¡Ω∏ˆ¡⁄±ﬂ»˝Ω«–Œ£¨ø¥∆‰Õ‚Ω”‘≤ «∑Ò∞¸∫¨ID∂•µ„£¨»Áπ˚∞¸∫¨£¨‘Ú∏¸ªª∂‘Ω«œﬂ
				for(int i=0;i<=1;i++){
					if(pnewIDtri[i]->p[1]!=NULL){
                        count++;
						flip(pnewIDtri[i]->p[1],pnewIDtri[i],ID,v,vlist,pIDtriList,count);
                        count--;
					}
					
				}
                
                
			}else{//»Áπ˚edgeIDµƒ¡⁄æ”÷∏’Î≤ªø’
				// thirdID _________ID0
				//         \---2__ID/ \
				//pAdjIDtri \edgeID/\ 0\  pIDtri
				//           \ 3  /   \ \
				//            \  /__1___\\
				//            ID1        ID2
				CIDTriangle* pAdjIDtri=pIDtri->p[edgeID];
				int thirdindex=getIndexOfVert_inIDtri1notinIDtri2(pAdjIDtri,pIDtri);
				int thirdID=pAdjIDtri->vID[thirdindex];
				if(thirdindex==-1){
					cout<<"error thirdindex==-1"<<endl;
					continue;
				}
				//…˙≥…Àƒ∏ˆ–¬»˝Ω«–Œ
				myvector<CIDTriangle*> pnewIDtri;
				pnewIDtri.resize(4);
				pnewIDtri[0]=new CIDTriangle();
				pnewIDtri[1]=new CIDTriangle();
				pnewIDtri[2]=new CIDTriangle();
				pnewIDtri[3]=new CIDTriangle();
				//Œ™–¬»˝Ω«–Œ…Ë∂®∂•µ„(æ˘“‘÷––ƒµ„ID◊˜Œ™∆ ºµ„)
				pnewIDtri[0]->setvID(ID,ID2,ID0);
				pnewIDtri[1]->setvID(ID,ID1,ID2);
				pnewIDtri[2]->setvID(ID,ID0,thirdID);
				pnewIDtri[3]->setvID(ID,thirdID,ID1);
				//…Ë∂®–¬‘ˆ»˝Ω«–Œµƒ¡⁄Ω”÷∏’Î
				pnewIDtri[0]->setp(pnewIDtri[1],pIDtri->p[(edgeID+2)%3],pnewIDtri[2]);
				pnewIDtri[1]->setp(pnewIDtri[3],pIDtri->p[(edgeID+1)%3],pnewIDtri[0]);
				pnewIDtri[2]->setp(pnewIDtri[0],pAdjIDtri->p[(thirdindex+2)%3],pnewIDtri[3]);
				pnewIDtri[3]->setp(pnewIDtri[2],pAdjIDtri->p[thirdindex],pnewIDtri[1]);
				//∏¸–¬pIDtri¡⁄Ω”»˝Ω«–Œµƒ÷∏’Î
				//Õ®π˝ID2ID0œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pIDtri->p[(edgeID+2)%3];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pIDtri);
						if(index==-1)continue;
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[0]
						_pAdjIDtri->p[index]=pnewIDtri[0];
					}
                    
				}
				//Õ®π˝ID1ID2œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pIDtri->p[(edgeID+1)%3];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pIDtri);
						if(index==-1)continue;
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[0]
						_pAdjIDtri->p[index]=pnewIDtri[1];
					}
                    
				}
				//Õ®π˝ID0thirdIDœ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pAdjIDtri->p[(thirdindex+2)%3];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpAdjIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pAdjIDtri);
						if(index==-1)continue;
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[2]
						_pAdjIDtri->p[index]=pnewIDtri[2];
					}
                    
				}
				//Õ®π˝thirdIDID1œ‡¡⁄µƒ»˝Ω«–Œ÷∏’Î–ﬁ’˝
				{
					CIDTriangle*_pAdjIDtri=pAdjIDtri->p[thirdindex];
					if(_pAdjIDtri!=NULL){
						//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpAdjIDtri
						int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pAdjIDtri);
						if(index==-1)continue;
						//Ω´¥À÷∏’Î∏ƒŒ™÷∏œÚpnewIDtri[0]
						_pAdjIDtri->p[index]=pnewIDtri[3];
					}
                    
				}
                
                
				//Ω´–¬‘ˆ»˝Ω«–Œº”»ÎpIDtriList
				pIDtriList.push_back(pnewIDtri[0]);
				pIDtriList.push_back(pnewIDtri[1]);
				pIDtriList.push_back(pnewIDtri[2]);
				pIDtriList.push_back(pnewIDtri[3]);
				
				//Ω´pIDtri±Íº«Œ™removed
				pIDtri->removed=true;
				pAdjIDtri->removed=true;
				//Ω´pnewIDtri[0]~pnewIDtri[1]º”◊˜pIDtriµƒ∫¢◊”
				pIDtri->q.push_back(pnewIDtri[0]);
				pIDtri->q.push_back(pnewIDtri[1]);
				//Ω´pnewIDtri[2]~pnewIDtri[3]º”◊˜pAdjIDtriµƒ∫¢◊”
				pAdjIDtri->q.push_back(pnewIDtri[2]);
				pAdjIDtri->q.push_back(pnewIDtri[3]);
                int count=0;
				//“¿¥ŒºÏ≤È∏˜pnewIDtriµƒp[1]£¨ø¥∆‰Õ‚Ω”‘≤ «∑Ò∞¸∫¨ID∂•µ„£¨»Áπ˚∞¸∫¨£¨‘Ú∏¸ªª∂‘Ω«œﬂ
				for(int i=0;i<=3;i++){
					
					if(pnewIDtri[i]->p[1]!=NULL){
                        count++;
						flip(pnewIDtri[i]->p[1],pnewIDtri[i],ID,v,vlist,pIDtriList,count);
                        count--;
					}
					
				}
			}
		}else if(judge==1){//»Áπ˚¬‰‘⁄»˝Ω«–Œƒ⁄
			//Ω´v≤Â»ÎµΩpIDtriƒ⁄
			//÷±Ω”Ω´pIDtri∑÷¡—Œ™»˝∏ˆ»˝Ω«–Œ
			//           ID0
			//           /|\
			//          / | \
			//         / ID  \
			//        / /   \ \
			//       //       \\
			//     ID1 ------- ID2
			//pIDtriµƒ»˝∏ˆ∂•µ„
			int ID0=pIDtri->vID[0];
			int ID1=pIDtri->vID[1];
			int ID2=pIDtri->vID[2];
			//…˙≥…»˝∏ˆ–¬»˝Ω«–Œ
			myvector<CIDTriangle*> pnewIDtri;
			pnewIDtri.resize(3);
			pnewIDtri[0]=new CIDTriangle();
			pnewIDtri[1]=new CIDTriangle();
			pnewIDtri[2]=new CIDTriangle();
			//Œ™»˝∏ˆ–¬»˝Ω«–Œ…Ë∂®∂•µ„(æ˘“‘÷––ƒµ„ID◊˜Œ™∆ ºµ„)
			pnewIDtri[0]->setvID(ID,ID0,ID1);
			pnewIDtri[1]->setvID(ID,ID1,ID2);
			pnewIDtri[2]->setvID(ID,ID2,ID0);
			//…Ë∂®–¬‘ˆ»˝Ω«–Œµƒ¡⁄Ω”÷∏’Î
			pnewIDtri[0]->setp(pnewIDtri[2],pIDtri->p[0],pnewIDtri[1]);
			pnewIDtri[1]->setp(pnewIDtri[0],pIDtri->p[1],pnewIDtri[2]);
			pnewIDtri[2]->setp(pnewIDtri[1],pIDtri->p[2],pnewIDtri[0]);
			//∏¸–¬pIDtri¡⁄Ω”»˝Ω«–Œµƒ÷∏’Î
			bool error=false;
			for(int i=0;i<=2;i++){
				//∏¸–¬pIDtri->p[i]µƒ÷∏’Î
				CIDTriangle*_pAdjIDtri=pIDtri->p[i];
				//∏¸–¬_pAdjIDtriµƒ÷∏’Î
				if(_pAdjIDtri!=NULL){
					//ø¥_pAdjIDtriµƒƒƒ∏ˆ÷∏’Î÷∏œÚpIDtri
					int index=getIndexOfp_IDtri1ToIDtri2(_pAdjIDtri,pIDtri);
					if(index==-1){
						error=true;
						break;
					}
					//Ω´¥À÷∏’Î÷∏œÚpnewIDtri[i]
					_pAdjIDtri->p[index]=pnewIDtri[i];
				}
			}
			if(error)continue;
			//Ω´–¬‘ˆ»˝Ω«–Œº”»ÎpIDtriList
			pIDtriList.push_back(pnewIDtri[0]);
			pIDtriList.push_back(pnewIDtri[1]);
			pIDtriList.push_back(pnewIDtri[2]);
			
			//Ω´pIDtri±Íº«Œ™removed
			pIDtri->removed=true;
			//Ω´pnewIDtri[0]~pnewIDtri[2]º”◊˜pIDtriµƒ∫¢◊”
			pIDtri->q.push_back(pnewIDtri[0]);
			pIDtri->q.push_back(pnewIDtri[1]);
			pIDtri->q.push_back(pnewIDtri[2]);
            int count=0;
			//“¿¥ŒºÏ≤È∏˜pnewIDtriµƒp[1]µƒ»˝∏ˆ¡⁄±ﬂ»˝Ω«–Œ£¨ø¥∆‰Õ‚Ω”‘≤ «∑Ò∞¸∫¨ID∂•µ„£¨»Áπ˚∞¸∫¨£¨‘Ú∏¸ªª∂‘Ω«œﬂ
			for(int i=0;i<=2;i++){
				
				if(pnewIDtri[i]->p[1]!=NULL){
                    count++;
					flip(pnewIDtri[i]->p[1],pnewIDtri[i],ID,v,vlist,pIDtriList,count);
                    count--;
				}
				
			}
		}else{//judge==3£¨±Ì æ¬‰‘⁄∂•µ„…œ
			
			continue;
		}
	}
	//…æ≥˝”Î≥¨º∂»˝Ω«–Œ∂•µ„œ‡πÿµƒ»˝Ω«–Œ
	//À—À˜pIDtriList£¨Ω´∫¨”–ID0,ID1,ID2÷Æ“ªµƒ»˝Ω«–Œ±ÍŒ™removed
	int nIDtri=(int)pIDtriList.size();
	for(int i=0;i<nIDtri;i++){
		CIDTriangle*pIDtri=pIDtriList[i];
		int _ID0,_ID1,_ID2;//pIDtriµƒ»˝∏ˆ∂•µ„ID
		_ID0=pIDtri->vID[0];
		_ID1=pIDtri->vID[1];
		_ID2=pIDtri->vID[2];
		if(_ID0==ID0||_ID0==ID1||_ID0==ID2
           ||_ID1==ID0||_ID1==ID1||_ID1==ID2
           ||_ID2==ID0||_ID2==ID1||_ID2==ID2){
			pIDtri->removed=true;
		}
	}
	//…æ≥˝_vlist÷–≥¨º∂»˝Ω«–Œ»˝∏ˆ∂•µ„
	vlist.pop_back();
	vlist.pop_back();
	vlist.pop_back();
}
vector<CIDTriangle> Delaunay(vector<Cv4>&vlist){
    //----cal vlist's range
    float xmin=inf;
    float xmax=-inf;
    float zmin=inf;
    float zmax=-inf;
    float ymin=inf;
    float ymax=-inf;
    int nv=(int)vlist.size();
    for(int i=0;i<nv;i++){
        float x=vlist[i].v[X];
        float y=vlist[i].v[Y];
        float z=vlist[i].v[Z];
        if(x<xmin)xmin=x;
        if(x>xmax)xmax=x;
        if(y<ymin)ymin=y;
        if(y>ymax)ymax=y;
        if(z<zmin)zmin=z;
        if(z>zmax)zmax=z;
    }//got xmin,xmax,ymin,ymax,zmin,zmax
    //----convert vector<Cv4> to myvector<Cv4>
    myvector<Cv4> _vlist;
    for(int i=0;i<nv;i++){
        _vlist.push_back(vlist[i]);
    }//get _vlist
    //----call Deluanay
    myvector<CIDTriangle*> pIDtriList;
    Delaunay(_vlist,xmin,xmax,zmin,zmax,pIDtriList);
    //----convert pIDtriList to IDtriList
    vector<CIDTriangle> IDtriList;
    int nIDtri=(int)pIDtriList.size();
    for(int i=0;i<nIDtri;i++){
        if(pIDtriList[i]->removed)continue;
        IDtriList.push_back(*pIDtriList[i]);
    }
    //----release pIDtriList
    for(int i=0;i<nIDtri;i++){
        delete pIDtriList[i];
    }
    pIDtriList.clear();
    //----return result
    return IDtriList;
    
}
vector<CIDTriangle> Delaunay(vector<Cv2>&vlist){
    //----convert vector<Cv2> to vector<Cv4>
    vector<Cv4> _vlist;
    int nv=(int)vlist.size();
    for(int i=0;i<nv;i++){
        Cv4 v(vlist[i].v[0],0,vlist[i].v[1],1);
        _vlist.push_back(v);
    }//got _vlist
    //----call Delaunay
    return Delaunay(_vlist);
}