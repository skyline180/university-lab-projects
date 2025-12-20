document.addEventListener('DOMContentLoaded', function() {
    // Mock posts data - in a real application, fetch this from a server
    const posts = [
        { title: "First Post", content: "This is the content of the first post." },
        { title: "Another Post", content: "Here is some more content for the second post." }
    ];

    const postsContainer = document.querySelector('.posts');

    posts.forEach(post => {
        const postElement = document.createElement('div');
        postElement.classList.add('post');
        postElement.innerHTML = `
            <h2>${post.title}</h2>
            <p>${post.content}</p>
        `;
        postsContainer.appendChild(postElement);
    });
});
