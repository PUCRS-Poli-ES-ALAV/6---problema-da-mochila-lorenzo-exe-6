import numpy

count = 0

def distEdRec(A, B):
    global count
    count += 1

    matriz = numpy.zeros((len(A) + 1, len(B) + 1))

    for t1 in range(len(A) + 1):
        count += 1
        matriz[t1][0] = t1

    for t2 in range(len(B) + 1):
        count += 1
        matriz[0][t2] = t2
        
    a = 0
    b = 0
    c = 0
    
    for t1 in range(1, len(A) + 1):
        for t2 in range(1, len(B) + 1):
            count += 1
            if (A[t1-1] == B[t2-1]):
                matriz[t1][t2] = matriz[t1 - 1][t2 - 1]
            else:
                a = matriz[t1][t2 - 1]
                b = matriz[t1 - 1][t2]
                c = matriz[t1 - 1][t2 - 1]
                
                if (a <= b and a <= c):
                    matriz[t1][t2] = a + 1
                elif (b <= a and b <= c):
                    matriz[t1][t2] = b + 1
                else:
                    matriz[t1][t2] = c + 1

    return int(matriz[len(A)][len(B)])   
 
#Assumindo os Custos: Remoção=R, Inserção=I , Substituição=S e Match=M=0;
def distEdProgDina(A, B):
    global count
    count += 1

    m = len(A)
    n = len(B)

    matriz = [0] * (m + 1)

    for i in range(m + 1):
        count += 1
        matriz[i] = [0] * (n + 1)

    for i in range(1, m + 1):
        count += 1
        matriz[i][0] = matriz[i - 1][0] + 1 #soma uma I

    for j in range(1, n + 1):
        count += 1
        matriz[0][j] = matriz[0][j - 1] + 1 #Soma uma R

    custoExtra = 0

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            count += 1
            if A[i - 1] == B[j - 1]:
                custoExtra = 0 #Operação M
            else:
                custoExtra = 1 #Operação S

            matriz[i][j] = min(matriz[i - 1][j] + 1, matriz[i][j - 1] + 1, matriz[i - 1][j - 1] + custoExtra)

    return matriz[m][n]

def reset():
    global count
    count = 0

s1: str = "Casablanca"
s2: str = "Portentoso"

reset()

print("distEdRec - Test 1")
print()
print("Result = ", distEdRec(s1, s2))
print("Number of instructions = ", count)
print()

reset()

print("distEdProgDina - Test 1")
print()
print("Result = ", distEdProgDina(s1, s2))
print("Number of instructions = ", count)
print()

reset()

s1: str = "Maven, a Yiddish word meaning accumulator of knowledge, began as an attempt to simplify the build processes in the Jakarta Turbine project. There were several  projects, each with their own Ant build files, that were all slightly different.JARs were checked into CVS. We wanted a standard way to build the projects, a clear definition of what the project consisted of, an easy way to publish project informationand a way to share JARs across several projects. The result is a tool that can now beused for building and managing any Java-based project. We hope that we have created something that will make the day-to-day work of Java developers easier and generally help with the comprehension of any Java-based project."
s2: str = "This post is not about deep learning. But it could be might as well. This is the power of kernels. They are universally applicable in any machine learning algorithm. Why you mightask? I am going to try to answer this question in this article. Go to the profile of Marin Vlastelica Pogančić Marin Vlastelica Pogančić Jun"

print("distEdRec - Test 2")
print()
print("Result = ", distEdRec(s1, s2))
print("Number of instructions = ", count)
print()

reset()

print("distEdProgDina - Test 2")
print()
print("Result = ", distEdProgDina(s1, s2))
print("Number of instructions = ", count)
print()