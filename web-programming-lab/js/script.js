//JS for Navigation bar menu icon
let menuList = document.querySelector(".nav .links");

function toggleMenu() {
  if (menuList.style.maxHeight === "0px" || menuList.style.maxHeight === "") {
    menuList.style.maxHeight = menuList.scrollHeight + "px"; // Expand to fit content
  } else {
    menuList.style.maxHeight = "0px"; // Collapse
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// JS for Dark Mode
function darkMoodOn() {
  document.body.classList.toggle("dark-mode");
}


















// JS for Journal & article Library
// // Configuration
//       const itemsPerPage = 5; // Number of items per page

//       // Data for demonstration
//       const allJournals = [
//         { title: "Journal of Clinical Psychology", category: "Research" },
//         { title: "Annual Review of Psychology", category: "Review" },
//         { title: "Case Studies in Mental Health", category: "Case Study" },
//         // Add more journals as needed
//       ];

//       const allArticles = [
//         { title: "Understanding Mental Health", category: "Editorial" },
//         { title: "Recent Advances in Therapy", category: "Feature" },
//         { title: "The Impact of Stress on Health", category: "Opinion" },
//         // Add more articles as needed
//       ];

//       // Journal functions
//       let currentJournalPage = 1;
//       let filteredJournals = [];

//       function displayJournals() {
//         const journalList = document.getElementById("journal-list");
//         journalList.innerHTML = "";

//         const startIndex = (currentJournalPage - 1) * itemsPerPage;
//         const endIndex = Math.min(
//           startIndex + itemsPerPage,
//           filteredJournals.length
//         );
//         const journalsToDisplay = filteredJournals.slice(startIndex, endIndex);

//         if (journalsToDisplay.length === 0) {
//           const noResults = document.createElement("li");
//           noResults.textContent = "No results found";
//           noResults.style.textAlign = "center";
//           noResults.style.padding = "1rem";
//           noResults.style.color = "#888";
//           journalList.appendChild(noResults);
//         } else {
//           journalsToDisplay.forEach((journal) => {
//             const listItem = document.createElement("li");
//             const highlightedTitle = highlightText(
//               journal.title,
//               document.getElementById("search-journal").value.toLowerCase()
//             );
//             listItem.innerHTML = `<a href="#">${highlightedTitle}</a>`;
//             journalList.appendChild(listItem);
//           });
//         }

//         document.getElementById("prev-journal-btn").disabled =
//           currentJournalPage === 1;
//         document.getElementById("next-journal-btn").disabled =
//           endIndex >= filteredJournals.length;
//       }

//       function searchJournal() {
//         const query = document
//           .getElementById("search-journal")
//           .value.toLowerCase();
//         filteredJournals = allJournals.filter((journal) =>
//           journal.title.toLowerCase().includes(query)
//         );
//         currentJournalPage = 1; // Reset to the first page
//         displayJournals();
//       }

//       function changeJournalPage(direction) {
//         const newPage = currentJournalPage + direction;
//         if (
//           newPage > 0 &&
//           (newPage - 1) * itemsPerPage < filteredJournals.length
//         ) {
//           currentJournalPage = newPage;
//           displayJournals();
//         }
//       }

//       function filterJournalCategory(category) {
//         const query = document
//           .getElementById("search-journal")
//           .value.toLowerCase();
//         filteredJournals = allJournals.filter((journal) => {
//           return (
//             (category === "All" || journal.category === category) &&
//             journal.title.toLowerCase().includes(query)
//           );
//         });
//         currentJournalPage = 1; // Reset to the first page
//         displayJournals();
//       }

//       // Article functions
//       let currentArticlePage = 1;
//       let filteredArticles = [];

//       function displayArticles() {
//         const articleList = document.getElementById("article-list");
//         articleList.innerHTML = "";

//         const startIndex = (currentArticlePage - 1) * itemsPerPage;
//         const endIndex = Math.min(
//           startIndex + itemsPerPage,
//           filteredArticles.length
//         );
//         const articlesToDisplay = filteredArticles.slice(startIndex, endIndex);

//         if (articlesToDisplay.length === 0) {
//           const noResults = document.createElement("li");
//           noResults.textContent = "No results found";
//           noResults.style.textAlign = "center";
//           noResults.style.padding = "1rem";
//           noResults.style.color = "#888";
//           articleList.appendChild(noResults);
//         } else {
//           articlesToDisplay.forEach((article) => {
//             const listItem = document.createElement("li");
//             const highlightedTitle = highlightText(
//               article.title,
//               document.getElementById("search-article").value.toLowerCase()
//             );
//             listItem.innerHTML = `<a href="#">${highlightedTitle}</a>`;
//             articleList.appendChild(listItem);
//           });
//         }

//         document.getElementById("prev-article-btn").disabled =
//           currentArticlePage === 1;
//         document.getElementById("next-article-btn").disabled =
//           endIndex >= filteredArticles.length;
//       }

//       function searchArticle() {
//         const query = document
//           .getElementById("search-article")
//           .value.toLowerCase();
//         filteredArticles = allArticles.filter((article) =>
//           article.title.toLowerCase().includes(query)
//         );
//         currentArticlePage = 1; // Reset to the first page
//         displayArticles();
//       }

//       function changeArticlePage(direction) {
//         const newPage = currentArticlePage + direction;
//         if (
//           newPage > 0 &&
//           (newPage - 1) * itemsPerPage < filteredArticles.length
//         ) {
//           currentArticlePage = newPage;
//           displayArticles();
//         }
//       }

//       function filterArticleCategory(category) {
//         const query = document
//           .getElementById("search-article")
//           .value.toLowerCase();
//         filteredArticles = allArticles.filter((article) => {
//           return (
//             (category === "All" || article.category === category) &&
//             article.title.toLowerCase().includes(query)
//           );
//         });
//         currentArticlePage = 1; // Reset to the first page
//         displayArticles();
//       }

//       function highlightText(text, query) {
//         if (!query.trim()) return text;
//         const regex = new RegExp(`(${query})`, "gi");
//         return text.replace(regex, '<span class="highlight">$1</span>');
//       }

//       // Initial display
//       displayJournals();
//       displayArticles();




console.log("Runnig Successfully!")



// JS for Journal Book Library

// const itemsPerPage = 5; // Number of books per page
//       let currentPage = 1;
//       let filteredBooks = []; // Store the filtered books

//       // Book data for demonstration
//       const allBooks = [
//         { title: "The Great Gatsby", category: "Fiction" },
//         { title: "Becoming", category: "Non-Fiction" },
//         { title: "The Power of Habit", category: "Self-Help" },
//         { title: "1984", category: "Fiction" },
//         { title: "Educated", category: "Non-Fiction" },
//         { title: "Atomic Habits", category: "Self-Help" },
//         { title: "To Kill a Mockingbird", category: "Fiction" },
//         // Add more books if needed
//       ];

//       function displayBooks() {
//         const bookList = document.getElementById("book-list");
//         bookList.innerHTML = "";

//         // Determine start and end index for current page
//         const startIndex = (currentPage - 1) * itemsPerPage;
//         const endIndex = startIndex + itemsPerPage;
//         const booksToDisplay = filteredBooks.slice(startIndex, endIndex);

//         if (booksToDisplay.length === 0) {
//           const noResults = document.createElement("li");
//           noResults.textContent = "No results found";
//           noResults.style.textAlign = "center";
//           noResults.style.padding = "1rem";
//           noResults.style.color = "#888";
//           bookList.appendChild(noResults);
//         } else {
//           booksToDisplay.forEach((book) => {
//             const listItem = document.createElement("li");
//             const highlightedTitle = highlightText(
//               book.title,
//               document.getElementById("search-books").value.toLowerCase()
//             );
//             listItem.innerHTML = `<a href="#">${highlightedTitle}</a>`;
//             bookList.appendChild(listItem);
//           });
//         }

//         // Update button states
//         document.getElementById("prev-btn").disabled = currentPage === 1;
//         document.getElementById("next-btn").disabled =
//           endIndex >= filteredBooks.length;
//       }

//       function searchBooks() {
//         const query = document
//           .getElementById("search-books")
//           .value.toLowerCase();
//         filteredBooks = allBooks.filter((book) =>
//           book.title.toLowerCase().includes(query)
//         );
//         currentPage = 1; // Reset to the first page
//         displayBooks();
//       }

//       function changePage(direction) {
//         const newPage = currentPage + direction;
//         if (
//           newPage > 0 &&
//           (newPage - 1) * itemsPerPage < filteredBooks.length
//         ) {
//           currentPage = newPage;
//           displayBooks();
//         }
//       }

//       function highlightText(text, query) {
//         const regex = new RegExp(`(${query})`, "gi");
//         return text.replace(regex, '<span class="highlight">$1</span>');
//       }

//       function filterCategory(category) {
//         const query = document
//           .getElementById("search-books")
//           .value.toLowerCase();
//         filteredBooks = allBooks.filter((book) => {
//           return (
//             (category === "All" || book.category === category) &&
//             book.title.toLowerCase().includes(query)
//           );
//         });
//         currentPage = 1; // Reset to the first page
//         displayBooks();
//       }

//       // Initial display
//       displayBooks();
























console.log("Running Scucessfully!");