import { Body, Controller, Get, Post, Render } from '@nestjs/common';
import { SendKoordinaterDto } from '../dto/SendKoordinaterDto';
import { KoordinaterService } from '../services/koordinater.service';

@Controller('koordinater')
export class KoordinaterController {
  constructor(private readonly koordinaterService: KoordinaterService) {}

  @Get()
  async getSisteKoordinater() {
    const koordinat = this.koordinaterService.getSisteKoordinat();
    return koordinat;
  }

  @Post()
  sendKoordinater(@Body() koordinat: SendKoordinaterDto) {
    console.log('POST:', koordinat);
  }
}
