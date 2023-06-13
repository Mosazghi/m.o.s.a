import { Injectable } from '@nestjs/common';
import { Model } from 'mongoose';
import { InjectModel } from '@nestjs/mongoose';
import { Koordinat } from '../schema/koordinat.schema';
import { SendKoordinaterDto } from '../dto/SendKoordinaterDto';

@Injectable()
export class KoordinaterService {
  constructor(
    @InjectModel('koordinat') private koordinatModel: Model<Koordinat>,
  ) {}

  async postKoordinat(
    createKoordinatDto: SendKoordinaterDto,
  ): Promise<Koordinat> {
    const res = new this.koordinatModel(createKoordinatDto);
    console.log('POST:', res);
    return res.save();
  }

  async getSisteKoordinat() {
    const koordinater = await this.koordinatModel
      .findOne()
      .sort({ _id: -1 })
      .exec();
    console.log('GET:', koordinater);
    return koordinater;
  }
}
