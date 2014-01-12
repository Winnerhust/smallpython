#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

#define ARRAY_INIT_SZIE 16

typedef unsigned int size_t ;
typedef void (*elem_delete_fun)(void *);
class Array
{
public:
	Array();
	Array(size_t length);
	~Array();

	size_t size(){return len;}
	size_t capacity(){return m_capacity;}
	
	bool empty() const{return len==0;}
	
	void resize(const size_t new_size);

	/*element */
	void * get_item(const size_t index);

	// if not found retrun -1
	long index(void *elem) const ;
	
	void * front(){return (char *)(data[0]);}
	void * back(){ return (char *)(data[len-1]);}
//	void  push_front(void *elem);
//	void  pop_front(void *elem);
	void  push_back(void *elem);
	void * pop_back();
	
	
	void erase(const size_t pos,const size_t length=1);
	void remove(void *elem);

	// clear all shoud define a function of deleting one item;
	void clear(elem_delete_fun elem_delete);
private:
	size_t len;
	size_t m_capacity;
	char ** data;

	size_t convert_to_capacity(const size_t length);
};

Array::Array():len(0),m_capacity(ARRAY_INIT_SZIE),data(NULL)
{
	data = (char **) malloc(ARRAY_INIT_SZIE*sizeof(int));
	assert(data);
}
Array::Array(size_t length):len(0),data(NULL)
{
	size_t mod = length%ARRAY_INIT_SZIE;
	m_capacity = length / ARRAY_INIT_SZIE;
	mod =( mod>0 ? 1:0);
	m_capacity += mod*ARRAY_INIT_SZIE;

	data = (char **) malloc(ARRAY_INIT_SZIE*sizeof(int ));
	assert(data);
}
Array::~Array()
{
	if(data)
		free(data);
}

size_t Array::convert_to_capacity(const size_t length)
{
	size_t mod = length%ARRAY_INIT_SZIE;
	size_t t_capacity = (length / ARRAY_INIT_SZIE)*ARRAY_INIT_SZIE;
	if(mod)
		t_capacity += ARRAY_INIT_SZIE;

	return t_capacity;
}
void Array::resize(const size_t new_size)
{
	size_t t_capacity = convert_to_capacity(new_size);
	if(t_capacity != m_capacity){

		m_capacity = t_capacity;
		char **tmp= (char **) realloc(data,m_capacity*sizeof(int));
		data= tmp;
		assert(data);
	}
}
void * Array::get_item(const size_t index)
{
	if(index >= len){
		printf("array index out of range\n");
		return NULL;
	}
	
	return data[index];
}
long Array::index(void *elem) const
{
	for(size_t i=0;i<len; ++i){
		if(elem == data[i]){
			return i;
		}
	}

	return -1;
}
	
void  Array::push_back(void *elem)
{
	if(len >= m_capacity){
		resize(m_capacity*2);
	}
	data[len]=(char *)elem;
	len++;

}
	
void * Array::pop_back()
{
	return data[--len];
}
	
void Array::erase(const size_t pos,const size_t length)
{
	size_t t;
	if(pos+length >=len){
		for(size_t i=pos;i<len;++i){
			data[i]=0;
		}
		len = len-pos >0 ? len-pos : 0;
		return ;
	}

	for(size_t i=pos+length;i <len ;++i){
		data[i-length]=data[i];
	}
	len = len -length;
}
void Array::remove(void *elem)
{
	size_t i = index(elem);
	if(i != 0){
		erase(i-1);
	}
}
void Array::clear(elem_delete_fun elem_delete)
{
	// cannot  for(i =len;i>=0;--i)
	// becase i-1 >0 where i=0, it would make error
	for(size_t i=len;i > 0;--i){
		cout<<"clear["<<i-1<<"]:";
		elem_delete(data[i-1]);
		data[i-1]=0;
	}
	len = 0;
}
/* for example: when the item is a pointer to string
void elem_delete(void *item)
{
	if(item){
		cout<<(char *)item<<endl;
		delete (char *)item;
	}
}
*/
int main(int argc,char *argv[])
{
	Array array(10);
	int k=0;
	int a=2,b=4,c=3,d=6;
	char e[]="python";
	char *f[5];
	for(int i=0;i<5;i++){
		f[i]= new char[20];
		sprintf(f[i],"a%dbc",i);
	}
	for(int i=0;i<5;i++){
		array.push_back(f[i]);
//		array.push_back(&b);
//		array.push_back(&c);
//		array.push_back(e);
	}
	for(int i=0;i<array.size();){
		cout<<(char *)array.get_item(i++)<<" "<<endl;
//		cout<<*(int *)array.get_item(i++)<<" "<<endl;
//		cout<<*(int *)array.get_item(i++)<<" "<<endl;
//		cout<<(char *)array.get_item(i++)<<" "<<endl;

	}
	assert(array.size()==5);
	array.clear(elem_delete);
	assert(array.size()==0);
/*	assert(array.size()==20);
	cout<<array.size()<<" "<<array.capacity()<<endl;
	int *q;
	q =(int *) array.pop_back();
	q =(int *) array.pop_back();
	q =(int *) array.pop_back();
	cout<<*q<<endl;
	assert(*q==4);
	assert(array.index(&c)==3);
	assert(array.size()==17);
	cout<<"index c:"<<array.index(&c)<<" "<<array.size()<<endl;
	array.erase(array.index(&c)-1);
	array.erase(array.index(&c)-1);
	array.erase(array.index(&c)-1);
	assert(array.size()==14);
	assert(array.index(&c)!=3);
	cout<<array.size()<<endl;
	assert(*(int *)array.get_item(0)==2);
//		cout<<*(int *)array.get_item(4)<<" "<<endl;
//		*/
	return 0;
}
