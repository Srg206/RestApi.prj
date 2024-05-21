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
    order_post_data=[{"district":10,"time":"2024-01-01 12:10:11","weight":4}]
    response_post = requests.post("http://127.0.0.1:8000/orders", json=order_post_data)
    response_get = requests.get("http://127.0.0.1:8000/orders")
    f.write("post/orders")
    f.write(str(response_post.status_code))
    f.write("\nget/orders")
    f.write(str(response_get.status_code))







