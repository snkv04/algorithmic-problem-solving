def main():
    N = int(input())
    x = [0] * N 
    y = [0] * N
    for i in range(N):
        s = input().split(" ")
        x[i] = int(s[0])
        y[i] = int(s[1])

    total_area = 0
    for i in range(1, N - 1):
        total_area += abs(x[0]*y[i]+x[i]*y[i+1]+x[i+1]*y[0] - y[0]*x[i]-y[i]*x[i+1]-y[i+1]*x[0])

    for i in range(1, N - 1):
        triangle_area = 2*abs(x[0]*y[i]+x[i]*y[i+1]+x[i+1]*y[0] - y[0]*x[i]-y[i]*x[i+1]-y[i+1]*x[0])
        total_area -= triangle_area
        if (total_area < 0):
            ratio = abs(total_area) / triangle_area
            ansx = x[i+1] + (x[i] - x[i+1]) * ratio
            ansy = y[i+1] + (y[i] - y[i+1]) * ratio
            print(ansx, " ", ansy)
            break

main()