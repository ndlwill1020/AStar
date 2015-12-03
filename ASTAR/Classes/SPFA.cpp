#include "SPFA.h"
#include <queue>
/*
2.1.SPFA�㷨��Ҫʲô
����SPFA��Ҫ�õ�һ���Ƚ��ȳ��Ķ���Q��
����SPFA��Ҫ��ͼ�е����ж�����һ����ʾ����ʾ���Ƿ��ڶ���Q�С������ù�ϣ����ӳ�䣬Ҳ����Ϊ��������һ���ֶΡ����ߵ�ʵ��Ч�ʸ��ߡ�

����2.2.SPFA������ִ�е�
����2.2.1 SPFA�ĳ�ʼ��
����SPFA�ĳ�ʼ����Dijkstra���ơ�
�����Ȱ����ж����·������ֵ��ʼ��Ϊ�������ֵ�����磺0x0FFFFFFF��
�������ж��㶼���Ϊ���ڶ����С�
������ʼ����������Q�С�
������ʼ�������ڶ����С�
������ʼ��������·������ֵ��Ϊ��Сֵ������0��
����Ȼ��������һ��ѭ��
����2.2.2 SPFAѭ��
����ѭ�������������Ƕ���QΪ�ա���һ�ν���ѭ����ʱ��ֻ����ʼ����һ��Ԫ�ء�
����ÿ��ѭ������������ͷ����һ�����㡣
�����������������г��߽����ɳڡ�����ɳڳɹ������ǳ����յ��϶�Ӧ���Ǹ������·������ֵ���ı��ˣ���������ɳڵĶ��㲻�ڶ���Q�У��Ͱ�������ɳڵĶ������Q��ע�⣬���ﶥ����ӵ�������2��1.�ɳڳɹ���2.�Ҳ��ڶ���Q�С�
����������Qû����Ԫ�ء��㷨������

*/

SPFA::SPFA(){

}

SPFA::~SPFA(){

}

/*
void Spfa( ͼG����ʼ����VStart )  
{  
    foreach( ��ͼG�е����ж�����б���,��������v��ʾ��������ÿһ���������  
    {  
        ���ö���v��·�����۹���ֵΪ�������ֵ�����磺0x0FFFFFFF  
        ���ñ�ʾ����v���ڶ�����  
        ����v��ǰ�����㶼Ϊ��  
    }  
    ��ʼ����VStart·�����۹���ֵΪ��Сֵ0  
    ��ʼ����VStart���Q  
  
    for( �������Q��Ϊ�գ�  
    {  
        ����Q����һ����ͷԪ��v  
        ��¼v�Ѿ����ڶ���Q����  
        for( �����Ӷ���Q�е����Ķ�ͷ����v��ÿһ�����ߣ�  
        {  
            u = ���յ��ϵĶ���   
            Relax( v , u�����ϵ�Ȩֵ��  
            if( Relax�ɳڳɹ��� && ����u���ڶ���Q�У�  
            {  
                u���Q  
                ��¼u�ڶ�������  
            }  
        }  
    }  
}  
*/

/*
��ӣ�������q.push(x); ��x �ӵ����е�ĩ�ˡ�
���ӣ�������q.pop(); �������еĵ�һ��Ԫ�أ�ע�⣬�����᷵�ر�����Ԫ�ص�ֵ��
���ʶ���Ԫ�أ�������q.front()�������类ѹ����е�Ԫ�ء�
���ʶ�βԪ�أ�������q.back()�������ѹ����е�Ԫ�ء�
�ж϶��пգ�������q.empty()�������п�ʱ������true��
���ʶ����е�Ԫ�ظ�����������q.size()
*/
void SPFA::execute(const Graph& Graph , const string& VetexId ){
	// ȡ��ͼ�Ķ��㼯��  
    const auto& Vertexes = Graph.GetVertexes( ) ;   
    //  ȡ����ʼ�������  
    Vertex *pVStart = Vertexes.find( VetexId )->second   ;  
  
    // Spfa�㷨��Ҫһ�����б��涥��  first-in first-out
    queue< Vertex* > Q ;   

	// ��ʼ��
	for ( auto& it : Vertexes )
	{
		Vertex *pV = it.second ; 

		pV->PathfindingData.Cost = 0x0FFFFFFF ;
		//IsInQueue[ pV ] = false ; 
		pV->PathfindingData.Flag = false ;
		pV->PathfindingData.pParent = nullptr ; // ����ĸ�·��������Ϊ��
	}
	pVStart->PathfindingData.Cost = 0 ;			// ��ʼ�����·������Ϊ0
	pVStart->PathfindingData.Flag = true ;		// ��ʼ�����ڶ�����
	//m_Ret.PathTree[ pVStart ] = 0 ;				//  ��ʼ����ĸ�·��Ϊ��
	Q.push( pVStart ) ;									// ��ʼ���������

	for (;Q.size()>0;)
	{
		auto pStartVertex = Q.front( ) ; 
		Q.pop( ) ;	// ���е���һ������v

		// �ɳڵ�����г���
		const auto& Eo = pStartVertex->GetEdgesOut( ) ;
		for ( auto& it : Eo )
		{
			auto pEdge = it.second ; 
			auto pEndVertex = pEdge->GetEndVertex( ) ;
			bool bRelaxRet = Relax( pStartVertex , pEndVertex , pEdge->GetWeight( ) ) ;
			if(bRelaxRet){
				// ������ڳ����ɳڳɹ����ҳ��߶�Ӧ���յ㶥�㲻�ڶ����еĻ����Ͳ����β
				if(pEndVertex->PathfindingData.Flag == false){
					Q.push( pEndVertex ) ;
					pEndVertex->PathfindingData.Flag = true ;//false
				}
			}
		}
	}
}

bool SPFA::Relax( Vertex* pStartVertex , Vertex* pEndVertex , int Weight ){
	int n = pStartVertex->PathfindingData.Cost + Weight;
	if(n<pEndVertex->PathfindingData.Cost){
		// ����·������  
        pEndVertex->PathfindingData.Cost = n ;  
        // ����·��  
        //m_Ret.PathTree[ pEndVertex ] = pStartVertex ;   
        pEndVertex->PathfindingData.pParent = pStartVertex ; 
		return true;//��ʾ������
	}
	return false;
}
