//
//  quadTree.cpp
//  HelloCpp
//
//  Created by ck02-084 on 13-11-29.
//
//

#include "quadTree.h"
namespace quadTree{
    Cv2 mul(float k,Cv2&v){
        Cv2 rs(v.x*k,v.y*k);
        return rs;
    }
    float distance(Cv2&v1,Cv2&v2){
        Cv2 diff=v1-v2;
        return sqrtf(diff.x*diff.x+diff.y*diff.y);
    }
    vector<CqNode*> CquadTree::getLeafList(){
        vector<CqNode*> leafList;
        getLeafList_inn(root,leafList);
        return leafList;
    }
    void CquadTree::clearTree(){
        clearTree_inn(root);
        root=NULL;
    }
    void CquadTree::debugDraw(){
        debugDraw_inn(root);
    }

    void CquadTree::initTree_inn(CqNode*&node)
    {
        Cv2 center=node->rect.getCenter();
        float d=distance(tgPoint,center);//distance between tgPoint and node center
        float e=node->rect.getWidth();//edge length of node
        if(e<=e_min)return;
        if(e>=e_max||d<e*C1){//divide the node into four child node
            //create four child node
            //   ---------
            //   | 3 | 2 |
            //   |---+---|
            //   | 0 | 1 |
            //   ---------
            CqNode*child0=new CqNode();
            CqNode*child1=new CqNode();
            CqNode*child2=new CqNode();
            CqNode*child3=new CqNode();
            child0->rect.init(node->rect.xmin,(node->rect.xmin+node->rect.xmax)/2,
                              node->rect.ymin,(node->rect.ymin+node->rect.ymax)/2);
            child1->rect.init((node->rect.xmin+node->rect.xmax)/2,node->rect.xmax,
                              node->rect.ymin,(node->rect.ymin+node->rect.ymax)/2);
            child2->rect.init((node->rect.xmin+node->rect.xmax)/2,node->rect.xmax,
                              (node->rect.ymin+node->rect.ymax)/2,node->rect.ymax);
            child3->rect.init(node->rect.xmin,(node->rect.xmin+node->rect.xmax)/2,
                              (node->rect.ymin+node->rect.ymax)/2,node->rect.ymax);
            //add children to node
            node->children.push_back(child0);
            node->children.push_back(child1);
            node->children.push_back(child2);
            node->children.push_back(child3);
            //do recursion for children
            int nchild=(int)node->children.size();
            for(int i=0;i<nchild;i++){
                initTree_inn(node->children[i]);
            }
        }else{//stop division
            return;
        }
    }
    
    void CquadTree::initTree(const Crect&rect,const Cv2&_tgPoint,float _e_min,float _e_max,float distanceResolution){
        assert(rect.getWidth()==rect.getHeight());
        //save C1
        C1=distanceResolution;
        //save tgPoint
        tgPoint=_tgPoint;
        //save e_min
        e_min=_e_min;
        //save e_max
        e_max=_e_max;
        //create root node for rect
        root=new CqNode();
        root->rect=rect;
        //build the tree recursively
        initTree_inn(root);
    }
    void CquadTree::getLeafList_inn(CqNode*&node,vector<CqNode*>&leafList){
        if(node==NULL)return;
        if((int)node->children.size()==0){//node is leaf
            //add node to leafList
            leafList.push_back(node);
        }else{
            //do recursion for children
            for(int i=0;i<(int)node->children.size();i++){
                getLeafList_inn(node->children[i],leafList);
            }
        }
        
    }
    void CquadTree::clearTree_inn(CqNode*&node)
    {
        if(node==NULL)return;
        //delete children first
        for(int i=0;i<(int)node->children.size();i++){
            clearTree_inn(node->children[i]);
        }
        //then delete node
        delete node;
    }
    void CquadTree::debugDraw_inn(CqNode*&node)
    {
        if(node==NULL)return;
        //draw node
        CCPoint vertices[]={ccp(node->rect.xmin,node->rect.ymin),
            ccp(node->rect.xmax,node->rect.ymin),
            ccp(node->rect.xmax,node->rect.ymax),
            ccp(node->rect.xmin,node->rect.ymax)};
        ccDrawPoly(vertices,4,true);
        //draw children
        for(int i=0;i<(int)node->children.size();i++){
            debugDraw_inn(node->children[i]);
        }
    }



}