/*SQL内部类型

INT | LONG   :LONG
FLOAT|DOUBLE :FLOAT
STRING       :CHAR *
TIME	     :TIME
NULL         :NULL
BOOL	     :TRUE/FALSE 0/非0  “”/非空串 非NULL/NULL
*/
#include <iostream>
using namespace std;

#define Py_ssize_t int

#define PyObjectHEAD \
	Py_ssize_t ob_refcnt;\
	struct typeobject *ob_type;
#define PyObject_VAR_HEAD \
	PyObjectHEAD \
	Py_ssize_t size;

#define PyTypeCheck(ob,t) ((ob)->ob_type->type == (t)) 
#define PyInt_Check(op) PyTypeCheck(ob,T_INT)
#define PyString_Check(op) PyTypeCheck(ob,T_STRING)

typedef struct PyObject{
	PyObjectHEAD
}PyObject;
typedef struct PyVarObject{
	PyObject_VAR_HEAD
}PyVarObject;
	
typedef struct _typeobject {
	enum {T_INT,T_LONG,T_FLOAT,T_DOUBLE,T_STRING,T_TIME,T_NULL,T_BOOL}type;
	void *type_ptr;

} PyTypeObject;

typedef struct PyIntObject{
	PyObjectHEAD
	int val;
}PyIntObject;
class IntTypeMethod
{
public:
	add(PyObject *w,PyObject *v);

};
int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

