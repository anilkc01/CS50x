document.addEventListener('DOMContentLoaded', () => {
    document.getElementById('contact-form').addEventListener('submit', function(event) {
        event.preventDefault(); // Prevent the default form submission

        // Get form data
        const formData = {
            name: document.getElementById('name').value,
            email: document.getElementById('email').value,
            subject: document.getElementById('subject').value,
            message: document.getElementById('message').value
        };

        // Send POST request to JSONBin API
        fetch('https://api.jsonbin.io/v3/b/66691084acd3cb34a85648d8', {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
                'X-Master-Key': '$2a$10$CbO2VeNXzNOW9gw2Dxd2z.qbDiHxVY9b/1LsTdRADVg4OcDggsgJO'
            },
            body: JSON.stringify(formData)
        })
        .then(response => response.json())
        .then(data => {
            console.log(data);
            alert('Your message has been sent successfully!');
        })
        .catch(error => {
            console.error('Error:', error);
            alert('There was an error sending your message.');
        });
    });
});
