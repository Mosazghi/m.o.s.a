const buttons = document.getElementsByClassName('drop-button');
const dropSted = document.getElementById('drop-sted');

// Interaktiv topdown
for (let i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', () => {
    dropSted.value = buttons[i].getAttribute('title');
  });
}

const liste = document.getElementById('liste').getElementsByTagName('tbody')[0]; // tabell body
const leggMerButton = document.getElementById('legg-mer-button');

leggMerButton.addEventListener('click', () => {
  let row = liste.insertRow();
  let kompNavn = row.insertCell(0);
  let ant = row.insertCell(1);

  kompNavn.innerHTML = document.getElementById('komponent').value;
  ant.innerHTML = document.getElementById('antall').value;
});

document.getElementById('bestill-button').addEventListener('click', sendData);

async function sendData() {
  const table = document.getElementById('liste');
  const komponenter = [];

  // Iterate over table rows (skipping the header row)
  for (let i = 1; i < table.rows.length; i++) {
    const row = table.rows[i];
    const rowData = {};

    // Iterate over table cells
    for (let j = 0; j < row.cells.length; j++) {
      const cell = row.cells[j];
      const columnName = table.rows[0].cells[j].innerText;
      const cellValue = cell.innerText;

      rowData[columnName] = cellValue;
    }

    komponenter.push(rowData);
  }

  let shoplist = [];

  shoplist.push(dropSted.value);
  shoplist.push(komponenter);
  console.log('form', shoplist);

  try {
    const res = await fetch('/dashboard/api/bestill', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(shoplist),
    });
    const data = await res.json();
    console.log('SENT: ', data, 'av: ', data.user.username);
  } catch (error) {
    console.error(error);
  }
}

async function getKomponenter() {
  const listeOerKomponenter = document.getElementById('komponent');
  const listeOverAntall = document.getElementById('antall');

  const komponenter = await fetch('/komponent/api/komponenter', {
    method: 'GET',
  });

  const data = await komponenter.json();

  for (let i = 0; i < data.length; i++) {
    const navn = data[i].navn;
    const valg = document.createElement('option');
    valg.value = valg.innerHTML = navn;
    listeOerKomponenter.appendChild(valg);

    valg.setAttribute('data-max', data[i].antall);
  }
}
getKomponenter();
const select = document.getElementById('komponent');
const quantityInput = document.getElementById('antall');
select.addEventListener('change', (event) => {
  const selectedOption = event.target.selectedOptions[0];
  const maxQuantity = selectedOption.getAttribute('data-max');
  quantityInput.setAttribute('max', maxQuantity);
});
