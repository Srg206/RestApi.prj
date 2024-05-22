import requests
import os
current_file_path = os.path.abspath(__file__)
project_dir = os.path.dirname(current_file_path)
os.chdir(project_dir)



with open('api_logs.txt', 'w') as f:
    # Записываем в файл
    #f.write(response_post)
    #f.write(response_get.text)
    #f.write("test")
    post_data=[{"district":10,"time":"2024-01-01 12:10:11","weight":4}]

    response= requests.post("http://127.0.0.1:8000/orders", json=post_data)
    f.write("\npost/orders---- ")
    f.write(str(response.status_code))

    response = requests.get("http://127.0.0.1:8000/orders")
    f.write("\nget/orders---- ")
    f.write(str(response.status_code))

    response = requests.get("http://127.0.0.1:8000/orders/1")
    f.write("\nget/orders/id---- ")
    f.write(str(response.status_code))


    post_data=[1]
    response=requests.post("http://127.0.0.1:8000/orders/complete", json=post_data)
    f.write("\npost/orders/complete---- ")
    f.write(str(response.status_code))


    post_data=[{"district":10,"time":"2024-01-01 12:10:11","type":"4"}]
    response=requests.post("http://127.0.0.1:8000/couriers", json=post_data)
    f.write("\npost/couriers---- ")
    f.write(str(response.status_code))

    post_data=[{"district":10,"time":"2024-01-01 12:10:11","type":"4"}]
    response=requests.get("http://127.0.0.1:8000/couriers", json=post_data)
    f.write("\nget/couriers---- ")
    f.write(str(response.status_code))

    response=requests.get("http://127.0.0.1:8000/couriers/1", json=post_data)
    f.write("\nget/couriers/id---- ")
    f.write(str(response.status_code))
    










