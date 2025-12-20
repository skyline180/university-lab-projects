// Configuration
const itemsPerPage = 5; // Number of items per page

// Data for demonstration
const allJournals = [
  { title: "Journal of Clinical Psychology", category: "Research", url: "https://www.example.com/journal-of-clinical-psychology" },
  { title: "Annual Review of Psychology", category: "Review", url: "https://www.example.com/annual-review-of-psychology" },
  { title: "Case Studies in Mental Health", category: "Case Study", url: "https://www.example.com/case-studies-in-mental-health" },
  { title: "Journal of Psychiatric Research", category: "Research", url: "https://www.example.com/journal-of-psychiatric-research" },
  { title: "Behavioral Sciences Review", category: "Review", url: "https://www.example.com/behavioral-sciences-review" },
  { title: "Trauma and Stress Studies", category: "Case Study", url: "https://www.example.com/trauma-and-stress-studies" }
];

const allArticles = [
  { title: "Understanding Mental Health", category: "Editorial", url: "https://www.example.com/understanding-mental-health" },
  { title: "Recent Advances in Therapy", category: "Feature", url: "https://www.example.com/recent-advances-in-therapy" },
  { title: "The Impact of Stress on Health", category: "Opinion", url: "https://www.example.com/impact-of-stress-on-health" },
  { title: "Cognitive Behavioral Therapy: A Comprehensive Guide", category: "Editorial", url: "https://www.example.com/cognitive-behavioral-therapy-guide" },
  { title: "Innovations in Psychiatric Treatment", category: "Feature", url: "https://www.example.com/innovations-in-psychiatric-treatment" },
  { title: "How Mindfulness Affects Mental Health", category: "Opinion", url: "https://www.example.com/mindfulness-and-mental-health" }
];


// Journal functions
let currentJournalPage = 1;
let filteredJournals = [];

function displayJournals() {
  const journalList = document.getElementById("journal-list");
  journalList.innerHTML = "";

  const startIndex = (currentJournalPage - 1) * itemsPerPage;
  const endIndex = Math.min(
    startIndex + itemsPerPage,
    filteredJournals.length
  );
  const journalsToDisplay = filteredJournals.slice(startIndex, endIndex);

  if (journalsToDisplay.length === 0) {
    const noResults = document.createElement("li");
    noResults.textContent = "No results found";
    noResults.style.textAlign = "center";
    noResults.style.padding = "1rem";
    noResults.style.color = "#888";
    journalList.appendChild(noResults);
  } else {
    journalsToDisplay.forEach((journal) => {
      const listItem = document.createElement("li");
      const highlightedTitle = highlightText(
        journal.title,
        document.getElementById("search-journal").value.toLowerCase()
      );
      listItem.innerHTML = `<a href="${journal.url}" target="_blank">${highlightedTitle}</a>`;
      journalList.appendChild(listItem);
    });
  }

  document.getElementById("prev-journal-btn").disabled =
    currentJournalPage === 1;
  document.getElementById("next-journal-btn").disabled =
    endIndex >= filteredJournals.length;
}

function searchJournal() {
  const query = document
    .getElementById("search-journal")
    .value.toLowerCase();
  filteredJournals = allJournals.filter((journal) =>
    journal.title.toLowerCase().includes(query)
  );
  currentJournalPage = 1; // Reset to the first page
  displayJournals();
}

function changeJournalPage(direction) {
  const newPage = currentJournalPage + direction;
  if (
    newPage > 0 &&
    (newPage - 1) * itemsPerPage < filteredJournals.length
  ) {
    currentJournalPage = newPage;
    displayJournals();
  }
}

function filterJournalCategory(category) {
  const query = document
    .getElementById("search-journal")
    .value.toLowerCase();
  filteredJournals = allJournals.filter((journal) => {
    return (
      (category === "All" || journal.category === category) &&
      journal.title.toLowerCase().includes(query)
    );
  });
  currentJournalPage = 1; // Reset to the first page
  displayJournals();
}

// Article functions
let currentArticlePage = 1;
let filteredArticles = [];

function displayArticles() {
  const articleList = document.getElementById("article-list");
  articleList.innerHTML = "";

  const startIndex = (currentArticlePage - 1) * itemsPerPage;
  const endIndex = Math.min(
    startIndex + itemsPerPage,
    filteredArticles.length
  );
  const articlesToDisplay = filteredArticles.slice(startIndex, endIndex);

  if (articlesToDisplay.length === 0) {
    const noResults = document.createElement("li");
    noResults.textContent = "No results found";
    noResults.style.textAlign = "center";
    noResults.style.padding = "1rem";
    noResults.style.color = "#888";
    articleList.appendChild(noResults);
  } else {
    articlesToDisplay.forEach((article) => {
      const listItem = document.createElement("li");
      const highlightedTitle = highlightText(
        article.title,
        document.getElementById("search-article").value.toLowerCase()
      );
      listItem.innerHTML = `<a href="${article.url}" target="_blank">${highlightedTitle}</a>`;
      articleList.appendChild(listItem);
    });
  }

  document.getElementById("prev-article-btn").disabled =
    currentArticlePage === 1;
  document.getElementById("next-article-btn").disabled =
    endIndex >= filteredArticles.length;
}

function searchArticle() {
  const query = document
    .getElementById("search-article")
    .value.toLowerCase();
  filteredArticles = allArticles.filter((article) =>
    article.title.toLowerCase().includes(query)
  );
  currentArticlePage = 1; // Reset to the first page
  displayArticles();
}

function changeArticlePage(direction) {
  const newPage = currentArticlePage + direction;
  if (
    newPage > 0 &&
    (newPage - 1) * itemsPerPage < filteredArticles.length
  ) {
    currentArticlePage = newPage;
    displayArticles();
  }
}

function filterArticleCategory(category) {
  const query = document
    .getElementById("search-article")
    .value.toLowerCase();
  filteredArticles = allArticles.filter((article) => {
    return (
      (category === "All" || article.category === category) &&
      article.title.toLowerCase().includes(query)
    );
  });
  currentArticlePage = 1; // Reset to the first page
  displayArticles();
}

function highlightText(text, query) {
  if (!query.trim()) return text;
  const regex = new RegExp(`(${query})`, "gi");
  return text.replace(regex, '<span class="highlight">$1</span>');
}

// Initial display
displayJournals();
displayArticles();
