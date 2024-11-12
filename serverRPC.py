from xmlrpc.server import SimpleXMLRPCServer

def Factorial(n):
    if(n<0):
        return -1
    fact=1
    for i in range(1,n+1):
        fact=fact*i
    return fact

def Cube(x):
    return x*x*x

server=SimpleXMLRPCServer(("localhost",8000),logRequests=False)
server.register_function(Factorial,'factorial_rpc')
server.register_function(Cube,"cube_rpc")

try:
    print("Server started on port no. ",8000)
    server.serve_forever()
except:
    print("Server is shuting down...")