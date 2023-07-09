import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  Patch,
  Post,
  Res,
} from '@nestjs/common';
import { CreateKomponentDto } from './dto/create-komponent.dto';
import { UpdateKomponentDto } from './dto/update-komponent.dto';
import { KomponentService } from './komponent.service';

@Controller('komponent')
export class KomponentController {
  constructor(private readonly komponentService: KomponentService) {}

  @Post('api/ny')
  create(@Body() createKomponentDto: CreateKomponentDto) {
    console.log(createKomponentDto);
    return this.komponentService.create(createKomponentDto);
  }

  @Get('api/komponenter')
  findAll() {
    return this.komponentService.findAll();
  }

  @Get('api/:id')
  findOne(@Param('id') id: string) {
    return this.komponentService.findOne(id);
  }

  @Patch('api/:id')
  async update(
    @Param('id') id: string,
    @Body('antall') antallBestilt: number,
    @Res() res,
  ) {
    const oppdatertKomponent = await this.komponentService.update(
      id,
      antallBestilt,
    );

    console.log(
      oppdatertKomponent
        ? `${oppdatertKomponent.navn} oppdatert med ${oppdatertKomponent.antall} igjen!`
        : 'Komponenten finnes ikke/ikke tilstrekklig igjen!',
    );

    oppdatertKomponent
      ? res.send(
          `${oppdatertKomponent.navn} oppdatert med ${oppdatertKomponent.antall} igjen!`,
        )
      : res.send('Komponenten finnes ikke/ikke tilstrekklig igjen!');
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.komponentService.remove(+id);
  }
}
