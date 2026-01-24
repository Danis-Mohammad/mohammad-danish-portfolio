import requests
import sys

def get_weather(city_name, api_key):
    # Base URL for OpenWeatherMap API
    base_url = "http://api.openweathermap.org/data/2.5/weather"
    
    # Parameters for the API request
    params = {
        'q': city_name,
        'appid': api_key,
        'units': 'metric'  # Use 'imperial' for Fahrenheit
    }

    print(f"\nFetching weather for {city_name}...\n")

    try:
        response = requests.get(base_url, params=params)
        data = response.json()

        # Check if the city was found (Status Code 200)
        if response.status_code == 200:
            # Extract specific data points
            temp = data['main']['temp']
            humidity = data['main']['humidity']
            description = data['weather'][0]['description']
            wind_speed = data['wind']['speed']

            # Display the data
            print("-" * 30)
            print(f"Weather in {city_name.title()}:")
            print(f"Condition:  {description.capitalize()}")
            print(f"Temperature: {temp}°C")
            print(f"Humidity:    {humidity}%")
            print(f"Wind Speed:  {wind_speed} m/s")
            print("-" * 30)
        
        elif data.get("cod") == "404":
            print("Error: City not found. Please check the spelling.")
        else:
            print(f"Error: Unable to fetch data. Status code: {response.status_code}")

    except requests.exceptions.RequestException as e:
        print(f"Connection Error: {e}")

if __name__ == "__main__":
    print("--- CLI Weather App ---")
    
    # Placeholder for your API Key
    # Replace 'YOUR_API_KEY_HERE' with your actual key
    API_KEY = "2d33d2efd1144de0a06dc9a95c160286" 
    
    if API_KEY == "YOUR_API_KEY_HERE":
        print("Setup Required: Please open the script and paste your OpenWeatherMap API key.")
    else:
        user_city = input("Enter city name or ZIP code: ")
        if user_city.strip():
            get_weather(user_city, API_KEY)
        else:
            print("Error: City name cannot be empty.")