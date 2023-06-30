//--------------------Interaktivt topdown (knapper)--------------------
const buttons = document.getElementsByClassName('drop-button');
const dropSted = document.getElementById('drop-sted');

for (let i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', () => {
    dropSted.value = buttons[i].getAttribute('title');
  });
}

//--------------------Legger til komponenter i tabell--------------------
const liste = document.getElementById('liste').getElementsByTagName('tbody')[0]; // tabell body
const leggMerButton = document.getElementById('legg-mer-button');

const erIkkeKomponent = 'Velg komponent' || '';

leggMerButton.addEventListener('click', () => {
  if (document.getElementById('komponent').value !== erIkkeKomponent) {
    let row = liste.insertRow();
    let kompNavn = row.insertCell(0);
    let ant = row.insertCell(1);

    kompNavn.innerHTML = document.getElementById('komponent').value;
    ant.innerHTML = document.getElementById('antall').value;

    for (let i = 0; i < liste.rows.length - 1; i++) {
      if (liste.rows[i].cells[0].innerHTML === kompNavn.innerHTML) {
        liste.deleteRow(liste.rows[i].rowIndex - 1);
      }
    }

    komponent.value = '';
    antall.value = '';
  }
});

//--------------------Sender data til serveren--------------------
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

//--------------------Henter komponenter fra databasen--------------------
async function getKomponenter() {
  const listeOverKomponenter = document.getElementById('komponent');
  let listeOverAntall = document.getElementById('antall');

  const komponenter = await fetch('/komponent/api/komponenter', {
    method: 'GET',
  });

  const data = await komponenter.json();

  for (let i = 0; i < data.length; i++) {
    const navn = data[i].navn;
    const antall = data[i].antall;

    if (antall) {
      const valg = document.createElement('option');
      valg.value = valg.innerHTML = navn;
      listeOverKomponenter.appendChild(valg);

      valg.setAttribute('data-max', data[i].antall);
    }
  }
  listeOverKomponenter.addEventListener('change', (e) => {
    const selectedOption = e.target.selectedOptions[0];
    const maxVal = selectedOption.getAttribute('data-max');
    listeOverAntall.value = maxVal;
    listeOverAntall.setAttribute('max', maxVal);
    listeOverAntall.setAttribute(
      'onkeyup',
      `if(this.value > ${maxVal}) this.value = ${maxVal}`,
    );
  });
}
getKomponenter();
