// JS for Journal Book Library
const itemsPerPage = 5; // Number of books per page
let currentPage = 1;
let filteredBooks = []; // Store the filtered books

// Updated book data with URLs
const allBooks = [
  { title: "The Great Gatsby", category: "Fiction", url: "https://www.gutenberg.org/ebooks/64317" },
  { title: "Becoming", category: "Non-Fiction", url: "https://www.goodreads.com/book/show/38746485-becoming" },
  { title: "The Power of Habit", category: "Self-Help", url: "https://www.goodreads.com/book/show/13618020-the-power-of-habit" },
  { title: "1984", category: "Fiction", url: "https://www.gutenberg.org/ebooks/84" },
  { title: "Educated", category: "Non-Fiction", url: "https://www.goodreads.com/book/show/35133922-educated" },
  { title: "Atomic Habits", category: "Self-Help", url: "https://www.goodreads.com/book/show/40121378-atomic-habits" },
  { title: "To Kill a Mockingbird", category: "Fiction", url: "https://www.goodreads.com/book/show/2657.To_Kill_a_Mockingbird" },
  { title: "The Body Keeps the Score: Brain, Mind, and Body in the Healing of Trauma", category: "Mental Health", url: "https://www.goodreads.com/book/show/18637340-the-body-keeps-the-score" },
  { title: "Thinking, Fast and Slow", category: "Mental Health", url: "https://www.goodreads.com/book/show/11468377-thinking-fast-and-slow" },
  { title: "Lost Connections: Uncovering the Real Causes of Depression – and the Unexpected Solutions", category: "Mental Health", url: "https://www.goodreads.com/book/show/37571271-lost-connections" },
  { title: "Daring Greatly: How the Courage to Be Vulnerable Transforms the Way We Live, Love, Parent, and Lead", category: "Mental Health", url: "https://www.goodreads.com/book/show/13588356-daring-greatly" },
  { title: "The Anxiety and Phobia Workbook", category: "Mental Health", url: "https://www.goodreads.com/book/show/1811468.The_Anxiety_and_Phobia_Workbook" },
  { title: "Feeling Good: The New Mood Therapy", category: "Mental Health", url: "https://www.goodreads.com/book/show/13981.Feeling_Good" },
  { title: "Man's Search for Meaning", category: "Mental Health", url: "https://www.goodreads.com/book/show/4069.Mans_Search_for_Meaning" },
  { title: "The Gifts of Imperfection: Let Go of Who You Think You're Supposed to Be and Embrace Who You Are", category: "Mental Health", url: "https://www.goodreads.com/book/show/7015405-the-gifts-of-imperfection" },
  { title: "The 4 Agreements: A Practical Guide to Personal Freedom", category: "Mental Health", url: "https://www.goodreads.com/book/show/6596.The_Four_Agreements" },
  { title: "Why Zebras Don't Get Ulcers: An Updated Guide to Stress, Stress-Related Diseases, and Coping", category: "Mental Health", url: "https://www.goodreads.com/book/show/290216.Why_Zebras_Dont_Get_Ulcers" }
];

function displayBooks() {
  const bookList = document.getElementById("book-list");
  bookList.innerHTML = "";

  // Determine start and end index for current page
  const startIndex = (currentPage - 1) * itemsPerPage;
  const endIndex = startIndex + itemsPerPage;
  const booksToDisplay = filteredBooks.slice(startIndex, endIndex);

  if (booksToDisplay.length === 0) {
    const noResults = document.createElement("li");
    noResults.textContent = "No results found";
    noResults.style.textAlign = "center";
    noResults.style.padding = "1rem"; //1rem = 16px
    noResults.style.color = "#888";
    bookList.appendChild(noResults);
  } else {
    booksToDisplay.forEach((book) => {
      const listItem = document.createElement("li");
      const highlightedTitle = highlightText(
        book.title,
        document.getElementById("search-books").value.toLowerCase()
      );
      listItem.innerHTML = `<a href="${book.url}" target="_blank">${highlightedTitle}</a>`;
      bookList.appendChild(listItem);
    });
  }

  // Update button states
  document.getElementById("prev-btn").disabled = currentPage === 1;
  document.getElementById("next-btn").disabled =
    endIndex >= filteredBooks.length;
}

function searchBooks() {
  const query = document.getElementById("search-books").value.toLowerCase();
  filteredBooks = allBooks.filter((book) =>
    book.title.toLowerCase().includes(query)
  );  //Filters the allBooks array for books whose titles include the query string. The result is stored in filteredBooks
  currentPage = 1; // Reset to the first page
  displayBooks();
}

function changePage(direction) {
  const newPage = currentPage + direction;
  if (
    newPage > 0 && (newPage - 1) * itemsPerPage < filteredBooks.length) {
    currentPage = newPage;
    displayBooks();
  }
}

function highlightText(text, query) {
  const regex = new RegExp(`(${query})`, "gi"); //'gi' -> global
  return text.replace(regex, '<span class="highlight">$1</span>');
}

function filterCategory(category) {
  const query = document.getElementById("search-books").value.toLowerCase();
  filteredBooks = allBooks.filter((book) => {
    return (
      (category === "All" || book.category === category) && book.title.toLowerCase().includes(query)
    );
  });
  currentPage = 1; // Reset to the first page
  displayBooks();
}

// Initial display
displayBooks();
