#include <stdio.h>
#include <math.h>

int p = 61;
int q = 53;

int euler= 0;
int n=0;
int e=0;
int d = 0;
int c = 0;
int m = 0;
int Encryption_Message=0;
int Decryption_Message=0;

int Calculate_n(int p, int q);
int Calculate_Totient_Function(int p, int q);
int GCD(int a, int b);
int Generate_PuplicKey(int Totient);
int Generate_PrivateKey(int Totient, int e);
int RSA_Encryption(int original_mess , int n , int e);
int RSA_Decryption(int Encrypted_Mes , int n,int d);

void RSA_Calc_Init(void)
{
    n = Calculate_n(p,q);
    euler = Calculate_Totient_Function(p,q);
    e = Generate_PuplicKey(euler);
    d = Generate_PrivateKey(euler,e);



}

int main()
{
    RSA_Calc_Init();

    printf("%d \n",n);
    printf("%d \n",euler);
    printf("%d \n",e);
    printf("%d \n",d);

    c = RSA_Encryption(65,n,e);

    m = RSA_Decryption(c,n,d);

    printf("Original Message: %d \n",65);
    printf("Encrypted Message: %d \n",c);
    printf("decrypted Message: %d \n",m);

    return 0;
}

int Calculate_n(int p, int q)
{
    //used in It is used as the modulus in both the encryption and decryption processes
    //it's purpose forms part of both the public and private keys in RSA
    int n = p * q;
    return n;
}

int Calculate_Totient_Function(int p, int q)
{
    //is a crucial step in the RSA algorithm. The totient function Q(n)is used to find the number of integers up to n that are coprime with n
    //For RSA, we use Q(n)to determine the private key exponent
    int Totient = (p-1)*(q-1);
    return Totient;
}
int GCD(int a, int b)
{
    //making sure the GCD is equal 1
	int t;
	while(1)
    {
		t= a%b;
		if(t==0)
			return b;
		a = b;
		b= t;
	}
}

int Generate_PuplicKey(int Totient)
{
    //puplic key is from 1<e<Q(n)
    //and GCD is Equal to 1
    //d×e≡1(mod Q(n))
    //there is a common choices for Puplic key its 3,17,65537
    int e = 17,temp;
    while(e<Totient)
    {
        temp = GCD(e,Totient);
        if(temp == 1)
            break;
        else
            e++;
    }
    return e;
}

int Generate_PrivateKey(int Totient, int e)
{
    int t = 0, newt = 1;
    int r = Totient, newr = e;
    int quotient, temp;
    while (newr != 0)
    {
        quotient = r / newr;
        temp = newt;
        newt = t - quotient * newt;
        t = temp; temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1)
        return -1;
    if (t < 0)
        t += Totient;
    return t;
}

int RSA_Encryption(int original_mess , int n , int e)
{
    //Compute Ciphertext c
    //c = m^e(mod(n))
    long long c = 1;
    for (int i = 0; i < e; i++)
        c = (c * original_mess) % n;
    return (int)c;
}
int RSA_Decryption(int Encrypted_Mes , int n,int d)
{
    //Compute Original Message
    //m = c^d(mod(n))
    long long int m = 1;
    for (int i = 0; i < d; i++)
        m = (m * Encrypted_Mes) % n;
    return (int)m;
}
